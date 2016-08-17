/*
 * File:	parser.c
 *
 * Description:	This file contains the public and private function and
 *		variable definitions for the recursive-descent parser for
 *		Simple C.
 */

# include <cstdlib>
# include <iostream>
# include "lexer.h"
# include "tokens.h"
# include "checker.h"

using namespace std;

static int lookahead, nexttoken;
static string lexbuf, nextbuf;
static Type returnType;

Type expression(bool &lvalue);
static void statement();


/*
 * Function:	error
 *
 * Description:	Report a syntax error to standard error.
 */

static void error()
{
    if (lookahead == DONE)
	report("syntax error at end of file");
    else
	report("syntax error at '%s'", lexbuf);

    exit(EXIT_FAILURE);
}


/*
 * Function:	match
 *
 * Description:	Match the next token against the specified token.  A
 *		failure indicates a syntax error and will terminate the
 *		program since our parser does not do error recovery.
 */

static void match(int t)
{
    if (lookahead != t)
	error();

    if (nexttoken) {
	lookahead = nexttoken;
	lexbuf = nextbuf;
	nexttoken = 0;
    } else
	lookahead = lexan(lexbuf);
}


/*
 * Function:	peek
 *
 * Description:	Return the next token in the input stream and save it so
 *		that match() will later return it.
 */

static int peek()
{
    if (!nexttoken)
	nexttoken = lexan(nextbuf);

    return nexttoken;
}


/*
 * Function:	expect
 *
 * Description:	Match the next token against the specified token, and
 *		return its lexeme.  We must save the contents of the buffer
 *		from the lexical analyzer before matching, since matching
 *		will advance to the next token.
 */

static string expect(int t)
{
    string buf = lexbuf;
    match(t);
    return buf;
}


/*
 * Function:	number
 *
 * Description:	Match the next token as a number and return its value.
 */

static unsigned long number()
{
    return strtoul(expect(NUM).c_str(), NULL, 0);
}


/*
 * Function:	isSpecifier
 *
 * Description:	Return whether the given token is a type specifier.
 */

static bool isSpecifier(int token)
{
    return token == INT || token == CHAR || token == STRUCT;
}


/*
 * Function:	specifier
 *
 * Description:	Parse a type specifier.  Simple C has only ints, chars, and
 *		structure types.
 *
 *		specifier:
 *		  int
 *		  char
 *		  struct identifier
 */

static string specifier()
{
    if (lookahead == INT || lookahead == CHAR)
	return expect(lookahead);

    match(STRUCT);
    return expect(ID);
}


/*
 * Function:	pointers
 *
 * Description:	Parse pointer declarators (i.e., zero or more asterisks).
 *
 *		pointers:
 *		  empty
 *		  * pointers
 */

static unsigned pointers()
{
    unsigned count = 0;


    while (lookahead == '*') {
	match('*');
	count ++;
    }

    return count;
}


/*
 * Function:	declarator
 *
 * Description:	Parse a declarator, which in Simple C is either a scalar
 *		variable or an array, with optional pointer declarators.
 *
 *		declarator:
 *		  pointers identifier
 *		  pointers identifier [ num ]
 */

static void declarator(const string &typespec)
{
    unsigned indirection;
    string name;


    indirection = pointers();
    name = expect(ID);

    if (lookahead == '[') {
	match('[');
	declareVariable(name, Type(typespec, indirection, number()));
	match(']');

    } else
	declareVariable(name, Type(typespec, indirection));
}


/*
 * Function:	declaration
 *
 * Description:	Parse a local variable declaration.  Global declarations
 *		are handled separately since we need to detect a function
 *		as a special case.
 *
 *		declaration:
 *		  specifier declarator-list ';'
 *
 *		declarator-list:
 *		  declarator
 *		  declarator , declarator-list
 */

static void declaration()
{
    string typespec;


    typespec = specifier();
    declarator(typespec);

    while (lookahead == ',') {
	match(',');
	declarator(typespec);
    }

    match(';');
}


/*
 * Function:	declarations
 *
 * Description:	Parse a possibly empty sequence of declarations.
 *
 *		declarations:
 *		  empty
 *		  declaration declarations
 */

static void declarations()
{
    while (isSpecifier(lookahead))
	declaration();
}


/*
 * Function:	primaryExpression
 *
 * Description:	Parse a primary expression.
 *
 *		primary-expression:
 *		  ( expression )
 *		  identifier ( expression-list )
 *		  identifier ( )
 *		  identifier
 *		  character
 *		  string
 *		  num
 *
 *		expression-list:
 *		  expression
 *		  expression , expression-list
 */

Type primaryExpression(bool &lvalue)
{
	Type left;

    if (lookahead == '(') {
		match('(');
		left = expression(lvalue);
		match(')');
		return left;
    } else if (lookahead == CHARACTER) {
		match(CHARACTER);
		lvalue = false;
		return Type("int", 0);
    } else if (lookahead == STRING) {
    	string s = lexbuf;
		match(STRING);
		lvalue = false;
		return Type("char", 0, s.length());
    } else if (lookahead == NUM) {
		match(NUM);
		lvalue = false;
		return Type("int", 0);
    } else if (lookahead == ID) {
		Symbol *s = checkIdentifier(expect(ID));
		left = s->type();
		if(left.isScalar())
			lvalue = true;
		else
			lvalue = false;

		if (lookahead == '(') {
		    match('(');
		    vector<Type> argList;

		    if (lookahead != ')') {
				argList.push_back(expression(lvalue));

				while (lookahead == ',') {
				    match(',');
				    argList.push_back(expression(lvalue));
				}
		    }
		    if(left.isFunction()){
		    	left = checkArgumentList(argList, s);
		    	lvalue = false;
		    }	
		    else{
		    	report("called object is not a function");
		    	left = Type();
		    }
		    match(')');
		}
		return left;
    } else
		error();
		return Type();
}	


/*
 * Function:	postfixExpression
 *
 * Description:	Parse a postfix expression.
 *
 *		postfix-expression:
 *		  primary-expression
 *		  postfix-expression [ expression ]
 *		  postfix-expression . identifier
 *		  postfix-expression -> identifier
 */

Type postfixExpression(bool &lvalue)
{
    Type left = primaryExpression(lvalue);
    Type right;

    while (1) {
	if (lookahead == '[') {
	    match('[');
	    right = expression(lvalue);
	    match(']');
	    left = checkIndexExpression(left, right);
	    lvalue = true;
	} else if (lookahead == '.') {
	    match('.');
	    left = checkDotExpression(left, lexbuf, lvalue);
	    match(ID);
	} else if (lookahead == ARROW) {
	    match(ARROW);
	    left = checkArrowExpression(left, lexbuf, lvalue);
	    match(ID);
	} else
	    break;
    }
    return left;
}


/*
 * Function:	prefixExpression
 *
 * Description:	Parse a prefix expression.
 *
 *		prefix-expression:
 *		  postfix-expression
 *		  ! prefix-expression
 *		  - prefix-expression
 *		  * prefix-expression
 *		  & prefix-expression
 *		  sizeof prefix-expression
 *		  sizeof ( specifier pointers )
 */

Type prefixExpression(bool &lvalue)
{
	Type left;

    if (lookahead == '!') {
	match('!');
	left = prefixExpression(lvalue);
	left = checkPrefixExpression(left, lvalue, "!");
	lvalue = false;

    } else if (lookahead == '-') {
	match('-');
	left = prefixExpression(lvalue);
	left = checkPrefixExpression(left, lvalue, "-");
	lvalue = false;

    } else if (lookahead == '*') {
	match('*');
	left = prefixExpression(lvalue);
	left = checkPrefixExpression(left, lvalue, "*");
	lvalue = true;

    } else if (lookahead == '&') {
	match('&');
	left = prefixExpression(lvalue);
	left = checkPrefixExpression(left, lvalue, "&");
	lvalue = false;

    } else if (lookahead == SIZEOF) {
		match(SIZEOF);

		if (lookahead == '(' && isSpecifier(peek())) {
		    match('(');
		    left = Type(specifier(), pointers());
		    match(')');
		} else
		    left = prefixExpression(lvalue);
		left = checkPrefixExpression(left, lvalue, "sizeof");
		lvalue = false;
    } else{
		left = postfixExpression(lvalue);
	}
	return left;
}


/*
 * Function:	castExpression
 *
 * Description:	Parse a cast expression.  If the token after the opening
 *		parenthesis is not a type specifier, we could have a
 *		parenthesized expression instead.
 *
 *		cast-expression:
 *		  prefix-expression
 *		  ( specifier pointers ) cast-expression
 */

Type castExpression(bool &lvalue)
{
	Type left;
	Type right;

    if (lookahead == '(' && isSpecifier(peek())) {
    	match('(');
		left = Type(specifier(), pointers());
		match(')');
		right = castExpression(lvalue);
		left = checkCastExpression(left, right);
		lvalue = false;

    } else
		left = prefixExpression(lvalue);

	return left;
}


/*
 * Function:	multiplicativeExpression
 *
 * Description:	Parse a multiplicative expression.
 *
 *		multiplicative-expression:
 *		  cast-expression
 *		  multiplicative-expression * cast-expression
 *		  multiplicative-expression / cast-expression
 *		  multiplicative-expression % cast-expression
 */

Type multiplicativeExpression(bool &lvalue)
{
    Type left = castExpression(lvalue);
    Type right;

    while (1) {
	if (lookahead == '*') {
	    match('*');
	    right = castExpression(lvalue);
	    left = checkMultiplicativeExpression(left, right, "*");
	    lvalue = false;

	} else if (lookahead == '/') {
	    match('/');
	    right = castExpression(lvalue);
	    left = checkMultiplicativeExpression(left, right, "/");
	    lvalue = false;

	} else if (lookahead == '%') {
	    match('%');
	    right = castExpression(lvalue);
	    left = checkMultiplicativeExpression(left, right, "%");
	    lvalue = false;

	} else
	    break;
    }
    return left;
}


/*
 * Function:	additiveExpression
 *
 * Description:	Parse an additive expression.
 *
 *		additive-expression:
 *		  multiplicative-expression
 *		  additive-expression + multiplicative-expression
 *		  additive-expression - multiplicative-expression
 */

Type additiveExpression(bool &lvalue)
{
    Type left = multiplicativeExpression(lvalue);
    Type right;

    while (1) {
	if (lookahead == '+') {
	    match('+');
	    right = multiplicativeExpression(lvalue);
	    left = checkAdditiveExpression(left, right, "+");
	    lvalue = false;

	} else if (lookahead == '-') {
	    match('-');
	    right = multiplicativeExpression(lvalue);
	    left = checkSubtractiveExpression(left, right, "-");
	    lvalue = false;

	} else
	    break;
    }
    return left;
}


/*
 * Function:	relationalExpression
 *
 * Description:	Parse a relational expression.  Note that Simple C does not
 *		have shift operators, so we go immediately to additive
 *		expressions.
 *
 *		relational-expression:
 *		  additive-expression
 *		  relational-expression < additive-expression
 *		  relational-expression > additive-expression
 *		  relational-expression <= additive-expression
 *		  relational-expression >= additive-expression
 */

Type relationalExpression(bool &lvalue)
{
    Type left = additiveExpression(lvalue);
    Type right;

    while (1) {
	if (lookahead == '<') {
	    match('<');
	    right = additiveExpression(lvalue);
	    left = checkEqualityExpression(left, right, "<");
	    lvalue = false;

	} else if (lookahead == '>') {
	    match('>');
	    right = additiveExpression(lvalue);
	    left = checkEqualityExpression(left, right, ">");
	    lvalue = false;

	} else if (lookahead == LEQ) {
	    match(LEQ);
	    right = additiveExpression(lvalue);
	    left = checkEqualityExpression(left, right, "<=");
	    lvalue = false;

	} else if (lookahead == GEQ) {
	    match(GEQ);
	    right = additiveExpression(lvalue);
	    left = checkEqualityExpression(left, right, ">=");
	    lvalue = false;

	} else
	    break;
    }
    return left;
}


/*
 * Function:	equalityExpression
 *
 * Description:	Parse an equality expression.
 *
 *		equality-expression:
 *		  relational-expression
 *		  equality-expression == relational-expression
 *		  equality-expression != relational-expression
 */

 Type equalityExpression(bool &lvalue)
 {
 	Type left = relationalExpression(lvalue);
 	Type right;

 	while(1){
 		if(lookahead == EQL){
 			match(EQL);
 			right = relationalExpression(lvalue);
 			left = checkEqualityExpression(left,right,"==");
 			lvalue = false;

 		}else if(lookahead == NEQ){
 			match(NEQ);
 			right = relationalExpression(lvalue);
 			left = checkEqualityExpression(left,right,"!=");
 			lvalue = false;

 		}else
 			break;
 	}
 	return left;
 }

/*
 * Function:	logicalAndExpression
 *
 * Description:	Parse a logical-and expression.  Note that Simple C does
 *		not have bitwise-and expressions.
 *
 *		logical-and-expression:
 *		  equality-expression
 *		  logical-and-expression && equality-expression
 */

Type logicalAndExpression(bool &lvalue)
{
    Type left = equalityExpression(lvalue);

    while (lookahead == AND) {
		match(AND);
		Type right = equalityExpression(lvalue);
		left = checkLogicalOr(left, right, "&&");
		lvalue = false;
    }
    return left;
}


/*
 * Function:	expression
 *
 * Description:	Parse an expression, or more specifically, a logical-or
 *		expression, since Simple C does not allow comma or
 *		assignment as an expression operator.
 *
 *		expression:
 *		  logical-and-expression
 *		  expression || logical-and-expression
 */

Type expression(bool &lvalue)
{
    Type left = logicalAndExpression(lvalue);

    while (lookahead == OR) {
		match(OR);
		Type right = logicalAndExpression(lvalue);
		left = checkLogicalOr(left, right, "||");
		lvalue = false;
    }
    return left;
}


/*
 * Function:	statements
 *
 * Description:	Parse a possibly empty sequence of statements.  Rather than
 *		checking if the next token starts a statement, we check if
 *		the next token ends the sequence, since a sequence of
 *		statements is always terminated by a closing brace.
 *
 *		statements:
 *		  empty
 *		  statement statements
 */

static void statements()
{
    while (lookahead != '}')
	statement();
}


/*
 * Function:	statement
 *
 * Description:	Parse a statement.  Note that Simple C has so few
 *		statements that we handle them all in this one function.
 *
 *		statement:
 *		  { declarations statements }
 *		  return expression ;
 *		  while ( expression ) statement
 *		  if ( expression ) statement
 *		  if ( expression ) statement else statement
 *		  expression = expression ;
 *		  expression ;
 */

static void statement()
{
	bool lvalue;
	Type left;
	Type right;

    if (lookahead == '{') {
	match('{');
	openScope();
	declarations();
	statements();
	closeScope();
	match('}');

    } else if (lookahead == RETURN) {
	match(RETURN);
	left = expression(lvalue);
	//left = Type(left.specifier(), left.indirection());
	checkStatement(left, returnType, "return", lvalue);
	match(';');

    } else if (lookahead == WHILE) {
	match(WHILE);
	match('(');
	left = expression(lvalue);
	checkStatement(left, right, "if", lvalue);
	match(')');
	statement();

    } else if (lookahead == IF) {
	match(IF);
	match('(');
	left = expression(lvalue);
	checkStatement(left, right, "if", lvalue);
	match(')');
	statement();

	if (lookahead == ELSE) {
	    match(ELSE);
	    statement();
	}

    } else {
		left = expression(lvalue);
		bool val = lvalue;
		if (lookahead == '=') {
		    match('=');
		    right = expression(lvalue);
			checkStatement(left, right, "=", val);
		}

		match(';');
    }
}


/*
 * Function:	parameter
 *
 * Description:	Parse a parameter, which in Simple C is always a scalar
 *		variable with optional pointer declarators.
 *
 *		parameter:
 *		  specifier pointers identifier
 */

static Type parameter()
{
    string typespec, name;
    unsigned indirection;


    typespec = specifier();
    indirection = pointers();
    name = expect(ID);

    Type type = Type(typespec, indirection);
    return declareParameter(name, type)->type();
}


/*
 * Function:	parameters
 *
 * Description:	Parse the parameters of a function, but not the opening or
 *		closing parentheses.
 *
 *		parameters:
 *		  void
 *		  parameter-list
 *
 *		parameter-list:
 *		  parameter
 *		  parameter , parameter-list
 */

static Parameters *parameters()
{
    Parameters *params = new Parameters();


    if (lookahead == VOID)
	match(VOID);

    else {
	params->push_back(parameter());

	while (lookahead == ',') {
	    match(',');
	    params->push_back(parameter());
	}
    }

    return params;
}


/*
 * Function:	topLevelDeclaration
 *
 * Description:	Parse a top level declaration, which is either a structure
 *		type definition, function definition, or global variable
 *		declaration.
 *
 *		type-definition:
 *		  struct identifier { declaration declarations } ;
 *
 *		global-declaration:
 *		  specifier global-declarator-list ;
 *
 *		global-declarator-list:
 *		  global-declarator
 *		  global-declarator , global-declarator-list
 *
 *		global-declarator:
 *		  pointers identifier
 *		  pointers identifier ( )
 *		  pointers identifier [ num ]
 *
 *		function-definition:
 *		  specifier pointers identifier ( parameters ) { ... }
 */

static void topLevelDeclaration()
{
    string typespec, name;
    unsigned indirection;


    typespec = specifier();

    if (typespec != "int" && typespec != "char" && lookahead == '{') {
	match('{');
	openScope();
	declaration();
	declarations();
	defineStructure(typespec, closeScope());
	match('}');
	match(';');

    } else {
	indirection = pointers();
	name = expect(ID);

	if (lookahead == '[') {
	    match('[');
	    declareVariable(name, Type(typespec, indirection, number()));
	    match(']');

	} else if (lookahead == '(') {
	    match('(');

	    if (lookahead == ')') {
		match(')');
		declareFunction(name, Type(typespec, indirection, nullptr));

	    } else {
		openScope();
		returnType = Type(typespec, indirection);
		defineFunction(name, Type(typespec, indirection, parameters()));
		match(')');
		match('{');
		declarations();
		statements();
		closeScope();
		match('}');
		return;
	    }

	} else
	    declareVariable(name, Type(typespec, indirection));

	while (lookahead == ',') {
	    match(',');
	    indirection = pointers();
	    name = expect(ID);

	    if (lookahead == '[') {
		match('[');
		declareVariable(name, Type(typespec, indirection, number()));
		match(']');

	    } else if (lookahead == '(') {
		match('(');
		match(')');
		declareFunction(name, Type(typespec, indirection, nullptr));

	    } else
		declareVariable(name, Type(typespec, indirection));
	}

	match(';');
    }
}


/*
 * Function:	main
 *
 * Description:	Analyze the standard input stream.
 */

int main()
{
    openScope();
    lookahead = lexan(lexbuf);

    while (lookahead != DONE)
	topLevelDeclaration();

    closeScope();
    exit(EXIT_SUCCESS);
}

/*
 * File:	lexer.cpp
 *
 * Description:	This file contains the public and private function and
 *		variable definitions for the lexical analyzer for Simple C.
 */

# include <cstdio>
# include <cctype>
# include <string>
# include <iostream>
# include "lexer.h"

using namespace std;
int numerrors, lineno = 1;

/* Later, we will associate token values with each keyword */

static string keywords[] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while",
};

# define numKeywords (sizeof(keywords) / sizeof(keywords[0]))

enum Token{
	AUTO = 256, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT,
	DO, DOUBLE, ELSE, ENUM, EXTERN, FLOAT, FOR, GOTO, IF, INT,
	LONG, REGISTER, RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT,
	SWITCH, TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE, WHILE,
	ID, STRING, NUMBER, CHARACTER,
	EQL, OR, AND, EQLEQL, NOTEQL, LTN, GTN, LEQ, GEQ, ADD, SUB,
	STAR, DIV, REM, ADDR, NOT, PLSPLS, NEGNEG, DOT, ARROW,
	LPAREN, RPAREN, LBRACK, RBRACK, LBRACE, RBRACE, SCOLON, COLON, COMMA, DONE
};

/*
 * Function:	report
 *
 * Description:	Report an error to the standard error prefixed with the
 *		line number.  We'll be using this a lot later with an
 *		optional string argument, but C++'s stupid streams don't do
 *		positional arguments, so we actually resort to snprintf.
 *		You just can't beat C for doing things down and dirty.
 */

void report(const string &str, const string &arg)
{
    char buf[1000];

    snprintf(buf, sizeof(buf), str.c_str(), arg.c_str());
    cerr << "line " << lineno << ": " << buf << endl;
    numerrors ++;
}


/*
 * Function:	lexan
 *
 * Description:	Read and tokenize the standard input stream.  The lexeme is
 *		stored in a buffer.
 */

int lexan(string &lexbuf)
{
    int p;
    unsigned i;
    static int c = cin.get();


    /* The invariant here is that the next character has already been read
       and is ready to be classified.  In this way, we eliminate having to
       push back characters onto the stream, merely to read them again. */

    while (!cin.eof()) {
	lexbuf.clear();


	/* Ignore white space */

	while (isspace(c)) {
	    if (c == '\n')
		lineno ++;

	    c = cin.get();
	}


	/* Check for an identifier or a keyword */

	if (isalpha(c) || c == '_') {
	    do {
		lexbuf += c;
		c = cin.get();
	    } while (isalnum(c) || c == '_');

	    for (i = 0; i < numKeywords; i ++)
		if (keywords[i] == lexbuf)
		    break;

	    if (i < numKeywords){
			return i+256;
		}
	    else{
			return ID;
		}

	/* Check for a number */

	} else if (isdigit(c)) {
	    do {
		lexbuf += c;
		c = cin.get();
	    } while (isdigit(c));

	    return NUMBER;


	/* There must be an easier way to do this.  It might seem stupid at
	   this point to recognize each token separately, but eventually
	   we'll be returning separate token values to the parser, so we
	   might as well do it now. */

	} else {
	    lexbuf += c;

	    switch(c) {


	    /* Check for '||' */

	    case '|':
		c = cin.get();

		if (c == '|') {
		    lexbuf += c;
		    c = cin.get();
		    return OR;
		}

		return true;


	    /* Check for '=' and '==' */

	    case '=':
		c = cin.get();

		if (c == '=') {
		    lexbuf += c;
		    c = cin.get();
			return EQLEQL;
		}

		return EQL;


	    /* Check for '&' and '&&' */

	    case '&':
		c = cin.get();

		if (c == '&') {
		    lexbuf += c;
		    c = cin.get();
			return AND;
		}

		return ADDR;


	    /* Check for '!' and '!=' */

	    case '!':
		c = cin.get();

		if (c == '=') {
		    lexbuf += c;
		    c = cin.get();
			return NOTEQL;
		}

		return NOT;


	    /* Check for '<' and '<=' */

	    case '<':
		c = cin.get();

		if (c == '=') {
		    lexbuf += c;
		    c = cin.get();
			return LEQ;
		}

		return LTN;


	    /* Check for '>' and '>=' */

	    case '>':
		c = cin.get();

		if (c == '=') {
		    lexbuf += c;
		    c = cin.get();
			return GEQ;
		}

		return GTN;


	    /* Check for '-', '--', and '->' */

	    case '-':
		c = cin.get();

		if (c == '-') {
		    lexbuf += c;
		    c = cin.get();
			return NEGNEG;
		} else if (c == '>') {
		    lexbuf += c;
		    c = cin.get();
			return ARROW;
		}

		return SUB;


	    /* Check for '+' and '++' */

	    case '+':
		c = cin.get();

		if (c == '+') {
		    lexbuf += c;
		    c = cin.get();
			return PLSPLS;
		}

		return ADD;


	    /* Check for simple, single character tokens */

	    case '*': 
	    c = cin.get();
	    return STAR;


	    case '%': 
	    c = cin.get();
	    return REM;
	    

	    case ':': 
	    c = cin.get();
	    return COLON;


	    case ';': 
	    c = cin.get();
	    return SCOLON;


	    case '(': 
	    c = cin.get();
	    return LPAREN;


	    case ')': 
		c = cin.get();
		return RPAREN;


		case '[': 
		c = cin.get();
		return LBRACK;


		case ']': 
		c = cin.get();
		return RBRACK;


	    case '{': 
	    c = cin.get();
	    return LBRACE;


	    case '}': 
	    c = cin.get();
	    return RBRACE;


	    case '.': 
	    c = cin.get();
	    return DOT;


	    case ',': 
	    c = cin.get();
	    return COMMA;


	    /* Check for '/' or a comment */

	    case '/':
		c = cin.get();

		if (c == '*') {
		    do {
			while (c != '*' && !cin.eof()) {
			    if (c == '\n')
				lineno ++;

			    c = cin.get();
			}

			c = cin.get();
		    } while (c != '/' && !cin.eof());

		    c = cin.get();
		    break;

		} else {
		    return DIV;
		}


	    /* Check for a string literal */

	    case '"':
		do {
		    p = c;
		    c = cin.get();
		    lexbuf += c;
		} while ((c != '"' || p == '\\') && c != '\n' && !cin.eof());

		if (c == '\n' || cin.eof())
		    report("malformed string literal");

		c = cin.get();
		return STRING;


	    /* Check for a character literal */

	    case '\'':
		do {
		    p = c;
		    c = cin.get();
		    lexbuf += c;
		} while ((c != '\'' || p == '\\') && c != '\n' && !cin.eof());

		if (c == '\n' || cin.eof() || lexbuf.size() == 2)
		    report("malformed character literal");

		c = cin.get();
		return CHARACTER;


	    /* Handle EOF here as well */

	    case EOF:
		return DONE;


	    /* Everything else is illegal */

	    default:
		c = cin.get();
		break;
	    }
	}
    }

    return DONE;
}


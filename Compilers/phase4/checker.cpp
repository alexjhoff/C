/*
 * File:	checker.cpp
 *
 * Description:	This file contains the public and private function and
 *		variable definitions for the semantic checker for Simple C.
 *
 *		Extra functionality:
 *		- inserting an undeclared symbol with the error type
 */

# include <map>
# include <iostream>
# include "lexer.h"
# include "checker.h"
# include "nullptr.h"
# include "tokens.h"
# include "Symbol.h"
# include "Scope.h"
# include "Type.h"


using namespace std;

static map<string,Scope*> fields;
static Scope *outermost, *toplevel;
static const Type error;

static string undeclared = "'%s' undeclared";
static string redefined = "redefinition of '%s'";
static string redeclared = "redeclaration of '%s'";
static string conflicting = "conflicting types for '%s'";
static string incomplete = "incomplete type for '%s'";
static string nonpointer = "pointer type required for '%s'";

static string E1 = "invalid return type";
static string E2 = "invalid type for test expression";
static string E3 = "lvalue required in expression";
static string E4 = "invalid operands to binary %s";
static string E5 = "invalid operand to unary %s";
static string E6 = "invalid operand in cast expression";
static string E7 = "invalid operand in sizeof expression";
static string E8 = "called object is not a function";
static string E9 = "invalid arguments to called function";
static string E10 = "using pointer to incomplete type";


/*
 * Function:	checkIfComplete
 *
 * Description:	Check if the given type is complete.  A non-structure type
 *		is always complete.  A structure type is complete if its
 *		fields have been defined.
 */

static Type checkIfComplete(const string &name, const Type &type)
{
    if (!type.isStruct() || type.indirection() > 0)
	return type;

    if (fields.count(type.specifier()) > 0)
	return type;

    report(incomplete, name);
    return error;
}

bool checkComplete( const Type &type)
{
    if (!type.isStruct() || type.indirection() > 0)
        return true;

    if (fields.count(type.specifier()) > 0)
        return true;

    return false;
}

/*
 * Function:	checkIfStructure
 *
 * Description:	Check if the given type is a structure.
 */

static Type checkIfStructure(const string &name, const Type &type)
{
    if (!type.isStruct() || type.indirection() > 0)
	return type;

    report(nonpointer, name);
    return error;
}


/*
 * Function:	openScope
 *
 * Description:	Create a scope and make it the new top-level scope.
 */

Scope *openScope()
{
    toplevel = new Scope(toplevel);

    if (outermost == nullptr)
	outermost = toplevel;

    return toplevel;
}


/*
 * Function:	closeScope
 *
 * Description:	Remove the top-level scope, and make its enclosing scope
 *		the new top-level scope.
 */

Scope *closeScope()
{
    Scope *old = toplevel;

    toplevel = toplevel->enclosing();
    return old;
}


/*
 * Function:	defineStructure
 *
 * Description:	Define a structure with the specified NAME and whose fields
 *		are specified by SCOPE.  A structure can be defined only
 *		once.
 */

void defineStructure(const string &name, Scope *scope)
{
    if (fields.count(name) > 0) {
	report(redefined, name);
	delete scope;
    } else
	fields[name] = scope;
}


/*
 * Function:	defineFunction
 *
 * Description:	Define a function with the specified NAME and TYPE.  A
 *		function is always defined in the outermost scope.  This
 *		definition always replaces any previous definition or
 *		declaration.
 */

Symbol *defineFunction(const string &name, const Type &type)
{
    Symbol *symbol = outermost->find(name);

    if (symbol != nullptr) {
	if (symbol->type().isFunction() && symbol->type().parameters()) {
	    report(redefined, name);
	    delete symbol->type().parameters();

	} else if (type != symbol->type())
	    report(conflicting, name);

	outermost->remove(name);
	delete symbol;
    }

    symbol = new Symbol(name, checkIfStructure(name, type));
    outermost->insert(symbol);

    return symbol;
}


/*
 * Function:	declareFunction
 *
 * Description:	Declare a function with the specified NAME and TYPE.  A
 *		function is always declared in the outermost scope.  Any
 *		redeclaration is discarded.
 */

Symbol *declareFunction(const string &name, const Type &type)
{
    Symbol *symbol = outermost->find(name);

    if (symbol == nullptr) {
	symbol = new Symbol(name, checkIfStructure(name, type));
	outermost->insert(symbol);

    } else if (type != symbol->type()) {
	report(conflicting, name);
	delete type.parameters();
    }

    return symbol;
}


/*
 * Function:	declareParameter
 *
 * Description:	Declare a parameter with the specified NAME and TYPE.  Any
 *		redeclaration is discarded.  The only difference between
 *		declaring a parameter and a variable is that a parameter
 *		cannot be a structure type.
 */

Symbol *declareParameter(const string &name, const Type &type)
{
    return declareVariable(name, checkIfStructure(name, type));
}


/*
 * Function:	declareVariable
 *
 * Description:	Declare a variable with the specified NAME and TYPE.  Any
 *		redeclaration is discarded.
 */

Symbol *declareVariable(const string &name, const Type &type)
{
    Symbol *symbol = toplevel->find(name);

    if (symbol == nullptr) {
	symbol = new Symbol(name, checkIfComplete(name, type));
	toplevel->insert(symbol);

    } else if (outermost != toplevel)
	report(redeclared, name);

    else if (type != symbol->type())
	report(conflicting, name);

    return symbol;
}


/*
 * Function:	checkIdentifier
 *
 * Description:	Check if NAME is declared.  If it is undeclared, then
 *		declare it as having the error type in order to eliminate
 *		future error messages.
 */

Symbol *checkIdentifier(const string &name)
{
    Symbol *symbol = toplevel->lookup(name);

    if (symbol == nullptr) {
	report(undeclared, name);
	symbol = new Symbol(name, error);
	toplevel->insert(symbol);
    }

    return symbol;
}


/*
 *      Expression Checks
 *
 *      Checks types of expressions
 */

bool isCompletePointer(Type &left)
{
    if(left.indirection() != 1)
        return true;
    if(left.isStruct())
        return true;
    if(fields.count(left.specifier()) > 0)
        return true;
    return false;
}


Type checkArgumentList(const vector<Type> argList, const Symbol *s)
{
    int i;

    if(s->type().parameters() == nullptr){
        for(i=0; i<argList.size(); i++){
            if(!argList[i].isSimple()){
                report(E9);
                return Type();
            }
        }
    }else{
        vector<Type> params = *(s->type().parameters());
        if(argList.size() != params.size()){
            report(E9);
            return Type();
        }
        for(i=0; i<argList.size(); i++){
            if(!argList[i].isCompatable(params[i])){
                report(E9);
                return Type();
            }
        }
        Type t = Type(s->type().specifier(), s->type().indirection());
        return t;
        //return s->type();
    }
    return s->type();
}

Type checkIndexExpression(Type &left, Type &right)
{
    left = left.promote();
    right = right.promote();
    if(left.isError() || right.isError())
        return Type();
    if(left.indirection() == 0){
        report(E4, "[]");
        return Type();
    }
    if(!checkComplete(left)){
        report(E10);
        return Type();
    }
    if(right.specifier() != "int" || right.indirection() != 0){
        report(E4, "[]");
        return Type();
    }
    return Type(left.specifier(), left.indirection() - 1);
}

Type checkDotExpression(Type &left, string p, bool &lvalue)
{
    if(left.isError())
        return Type();
    if(!left.isStruct() || left.indirection() != 0){
        report(E4, ".");
        return Type();
    }
    if(!(fields.count(left.specifier()) > 0)){
        report(E10);
        return Type();
    }
    if(fields[left.specifier()]->find(p) == NULL){
        report(E4, ".");
        return Type();
    }

    if(lvalue == true && !fields[left.specifier()]->find(p)->type().isArray())
        lvalue = true;
    else
        lvalue = false;
    return fields[left.specifier()]->find(p)->type();
}

Type checkArrowExpression(Type &left, string p, bool &lvalue)
{
    left = left.promote();
    if(left.isError())
        return Type();

    if(left.indirection() == 0 || !left.isScalar() || !left.isStruct()){
        report(E4, "->");
        return Type();
    }
    if(checkIfStructure(p, left) == Type() || !(fields.count(left.specifier()) > 0)){
        report(E10);
        return Type();
    }
    if(fields[left.specifier()]->find(p) == NULL){
        report(E4, "->");
        return Type();
    }
    if(!fields[left.specifier()]->find(p)->type().isArray())
        lvalue = true;
    else
        lvalue = false;
    return fields[left.specifier()]->find(p)->type();
}

Type checkPrefixExpression(Type &left, bool lvalue, string p)
{
    if(left.isError())
        return Type();
    if(p == "*"){
        left = left.promote();
        if(left.indirection() == 0){
            report(E5, p);
            return Type();
        }
        if(!checkComplete(left)){
            report(E10);
            return Type();
        }
        return Type(left.specifier(), left.indirection() - 1);
    }else if(p == "&"){
        if(lvalue == true)
            return Type(left.specifier(), left.indirection() + 1);
        report(E3);
        return Type();
    }else if(p == "!"){
        if(left.isSimple())
            return Type("int");
        report(E5, p);
        return Type();
    }else if(p == "-"){
        left = left.promote();
        if(left.specifier() == "int" && left.indirection() == 0)
            return Type("int");
        report(E5, p);
        return Type();
    }else if(p == "sizeof"){
        if(left.isFunction() && checkIfComplete("sizeof", left) == error)
            return Type("int");
        report(E7);
        return Type();
    }else
        return Type();
}

Type checkCastExpression(Type &left, Type &right)
{
    Type temp = left;
    left = left.promote();
    right = right.promote();
    if(left.isError() || right.isError())
        return Type();
    if(left.isSimple() && right.isSimple())
        return temp;
    else{
        report(E6);
        return Type();
    }
}

Type checkMultiplicativeExpression(Type &left, Type &right, string p)
{
    left = left.promote();
    right = right.promote();
    if(left.isError() || right.isError())
        return Type();
    if(left.specifier() == "int" && left.indirection() == 0 && right.specifier() == "int" && right.indirection() == 0)
        return Type("int");
    else{
        report(E4, p);
        return Type();
    }
}

Type checkSubtractiveExpression(Type &left, Type &right, string p)
{
    left = left.promote();
    right = right.promote();
    if(left.isError() || right.isError())
        return Type();
    if(left.specifier() == "int" && left.indirection() == 0 && right.specifier() == "int" && right.indirection() == 0)
        return Type("int");
    else if(left.indirection() != 0 && right.specifier() == "int" && right.indirection() == 0)
        return left;
    else if(right.indirection() != 0 && left.indirection() != 0)
        return Type("int");
    else{
        report(E4, p);
        return Type();
    }
}

Type checkAdditiveExpression(Type &left, Type &right, string p)
{
    left = left.promote();
    right = right.promote();
    if(left.isError() || right.isError())
        return Type();
    if(left.specifier() == "int" && left.indirection() == 0 && right.specifier() == "int" && right.indirection() == 0)
        return Type("int");
    else if(left.indirection() != 0 && right.specifier() == "int" && right.indirection() == 0)
        return left;
    else if(right.indirection() != 0 && left.specifier() == "int" && left.indirection() == 0)
        return right;
    else{
        report(E4, p);
        return Type();
    }
}

Type checkEqualityExpression(Type &left, Type &right, string p)
 {
    left = left.promote();
    right = right.promote();
    if(left.isError() || right.isError())
        return Type();
    if(!left.isCompatable(right)){
        report(E4, p);
        return Type();
    }
    return Type("int");
 }


Type checkLogicalOr(Type &left, Type &right, string p)
{
    left = left.promote();
    right = right.promote();
    if(left.isError() || right.isError())
        return Type();
    if(left.isSimple() && right.isSimple())
        return Type("int");
    report(E4, p);
    return Type();
}

void checkStatement(const Type &left, const Type &right, string p, bool lvalue)
{
    if(left.isError())
        return;
    if(p == "return"){
        if(!left.isCompareable(right))
            report(E1);
    }else if(p == "if"){
        if(!left.isSimple())
            report(E2);
    }else if(p == "="){
        if(lvalue == false){
            report(E3);
        }
        if(!left.isCompatable(right)){
            report(E4, p);
        }
    }

}

 


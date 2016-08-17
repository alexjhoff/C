/*
 * File:	checker.h
 *
 * Description:	This file contains the public function declarations for the
 *		semantic checker for Simple C.
 */

# ifndef CHECKER_H
# define CHECKER_H
# include "Scope.h"

Scope *openScope();
Scope *closeScope();

void defineStructure(const std::string&name, Scope *scope);

Symbol *defineFunction(const std::string &name, const Type &type);
Symbol *declareFunction(const std::string &name, const Type &type);
Symbol *declareParameter(const std::string &name, const Type &type);
Symbol *declareVariable(const std::string &name, const Type &type);
Symbol *checkIdentifier(const std::string &name);
bool checkComplete( const Type &type);

bool isCompletePointer(Type &left);
Type checkArgumentList(const std::vector<Type> argList, const Symbol *s);
Type checkIndexExpression(Type &left, Type &right);
Type checkArrowExpression(Type &left, std::string p, bool &lvalue);
Type checkDotExpression(Type &left, std::string p, bool &lvalue);
Type checkPrefixExpression(Type &left, bool lvalue, std::string p);
Type checkCastExpression(Type &left, Type &right);
Type checkMultiplicativeExpression(Type &left, Type &right, std::string p);
Type checkSubtractiveExpression(Type &left, Type &right, std::string p);
Type checkAdditiveExpression(Type &left, Type &right, std::string p);
Type checkEqualityExpression(Type &left, Type &right, std::string p);
Type checkLogicalOr(Type &left, Type &right, std::string p);
void checkStatement(const Type &left, const Type &right, std::string p, bool lvalue);

# endif /* CHECKER_H */

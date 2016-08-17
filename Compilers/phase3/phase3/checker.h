#ifndef CHECKER_H
#define CHECKER_H
#include <string>
#include <ostream>
#include <vector>
#include "scope.h"

bool lookup(Scope *start, const std::string &name); //check all scopes

Scope* openScope(Scope *old);

void decVar(Scope *current, Symbol *newS, std::vector<std::string> defined);

void defFunct(Scope *global, Symbol *newS);

void decParam(Scope *current, Symbol *newS);

#endif
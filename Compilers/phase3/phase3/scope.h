#ifndef SCOPE_H
#define SCOPE_H
#include <string>
#include <ostream>
#include <vector>
#include "symbol.h"


class Scope{
	typedef std::vector<Symbol *> Symbols;
	Scope *_enclosing;
	Symbols _symbols;
	typedef std::string string;

public:
	Scope(Scope *enclosing = NULL);
	Scope *enclosing();
	Symbols &symbols();
	void insert(Symbol *);
	Symbol *find(const string &name) const; //find in current scope
};


#endif
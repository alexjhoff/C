#include "scope.h"
#include <iostream>

using namespace std;


Scope::Scope(Scope *enclosing)
:_enclosing(enclosing)
{

}

Scope* Scope::enclosing()
{
	return _enclosing;
}

Scope::Symbols& Scope::symbols()
{
	return _symbols;
}

void Scope::insert(Symbol *next)
{
	_symbols.push_back(next);
}

Symbol* Scope::find(const string &name) const //find in current scope
{
	for(int i=0;i<_symbols.size();i++){
		if(_symbols[i]->name() == name){
			return _symbols[i];
		}
	}
	return NULL;
}
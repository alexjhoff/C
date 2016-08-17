#include <iostream>
#include "checker.h"
#include "lexer.h"

using namespace std;

vector<string> definedFuncs;

typedef std::vector<Symbol *> def;

bool lookup(Scope *start, const string &name) //find in all scopes
{
	Scope *newScope = start;
	const Symbol *temp = NULL;

	while(newScope != NULL){
		temp = newScope -> find(name);
		if(temp != NULL){ //find found the symbol
			return true;
		}
		else{
			newScope = newScope->enclosing();
		}
	}
	return false;
}

Scope* openScope(Scope *old)
{
	Scope *newScope = new Scope(old);
	return newScope;
}

void decVar(Scope *current, Symbol *newS, vector<string> defined)
{
	Symbol *temp = NULL;
	temp = current->find(newS->name());
	if(newS->type().specifier() != "int" && newS->type().specifier() != "char"){
		if(newS->type().kind() == FUNCTION){
			if(newS->type().indirection() == 0)
				report("pointer type required for '%s'", newS->name());
		}
		else{
			for(int i=0;i<defined.size();i++){				//check each defined funct
				if(defined[i] == newS->type().specifier()){	
					current->insert(newS);
					return;
				}
			}
			if(newS->type().indirection() == 0)	
				report("incomplete type for '%s'", newS->name());
		}
	}
	else if(temp == NULL){
		current->insert(newS);
	}
	else if(current->enclosing() != NULL)
		report("redeclaration of '%s'", newS->name());
	else if(temp->type() != newS->type())
		report("conflicting types for '%s'", newS->name());
}

//Q1: why is global->find(newS->name()) always returning null
void defFunct(Scope *global, Symbol *newS) //should defined be pointer?
{
	Symbol *temp;
	temp = global->find(newS->name());
		if(temp == NULL){
			global->insert(newS);
			definedFuncs.push_back(newS->name()); //add funct to defined funct list
		}
		else{										//function has been found either defined or not
			for(int i=0;i<definedFuncs.size();i++){				//check each defined funct
				if(definedFuncs[i] == temp->name()){				//defined funct already exists
					report("redefenition of '%s'", newS->name());
					return;
				}
			}
			definedFuncs.push_back(newS->name()); //add funct to defined funct list

			if(temp->type() != newS->type())
				report("conflicting types for '%s'", newS->name());
		}

		if(newS->type().specifier() != "int" && newS->type().specifier() != "char"){
			if(newS->type().indirection() == 0)
				report("pointer type required for '%s'", newS->name());
		}

		
		for(int i=0;i<global->symbols().size();i++){				//go through symbols
			if(newS->name() == global->symbols()[i]->name())		//find the correct symbol
				global->symbols()[i] = newS;						//swap it with the new type
		}
}

void decParam(Scope *current, Symbol *newS)
{
	Symbol *symbol = NULL;
	symbol = current->find(newS->name());
	if(symbol == NULL){
		if(newS->type().specifier() != "int" && newS->type().specifier() != "char" && newS->type().indirection() == 0)
			report("pointer type required for '%s'", newS->name());
		current->insert(newS);
	}
	else
		report("redeclaration of '%s'", newS->name());
}




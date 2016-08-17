#include "Tree.h"
#include <iostream>

using namespace std;

void Assignment::generate()
{
	cout << "\tmovl\t";
	_right->generate();
	cout << ", %eax" << endl;
	
	cout << "\tmovl\t";
	cout << "%eax, ";
	_left->generate();
	cout << endl;
}

void Function::generate()
{
	//preamble
	cout << _id->name() << ":" << endl;
	cout << "\tpushl\t" << "%ebp" << endl;
	cout << "\tmovl\t" << "%esp, %ebp" << endl;
	cout << "\tsubl\t$" << _id->name() << ".size, %esp" << endl;

	//body
	vector<Symbol*> vars = _body->declarations()->symbols();
	
	int i = 0, offset = 0;
	for(i=0; i<_id->type().parameters()->size(); i++)
		vars[i]->setOffset(8+4*i);
	for(; i<vars.size(); i++){
		offset -= vars[i]->type().size();
		vars[i]->setOffset(offset);
	}
	_body->generate();
	
	//epilogue
	cout << "\tmovl\t" << "%ebp, %esp" << endl;
	cout << "\tpopl\t" << "%ebp" << endl;
	cout << "\tret" << endl;
	cout << endl;
	cout << "\t.globl\t" << _id->name() << endl;
	cout << "\t.set\t" << _id->name() << ".size, " << -offset << endl;
}

void Identifier::generate()
{
	if(_symbol->offset() == 0)
		cout << _symbol->name();
	else
		cout << _symbol->offset() << "(%ebp)";
}

void Number::generate()
{
	cout << "$" << this->value();
}

void Block::generate()
{
	int i;
	for(i=0; i<_stmts.size(); i++)
		_stmts[i]->generate();
}

void Call::generate()
{
	//push args from right to left
	int i;
	for(i=_args.size()-1; i>=0; i--){
		cout << "\tpushl\t";
		_args[i]->generate();
		cout << endl;
	}

	//call function
	cout << "\tcall\t" << _id->name();
	cout << endl;

	//reset esp
	cout << "\taddl\t$" << 4*_args.size();
	cout << ", %esp" << endl;
}
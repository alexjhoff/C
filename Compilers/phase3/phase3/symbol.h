#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <ostream>
#include "type.h"


class Symbol{
	typedef std::string string;
	string _name;
	Type _type;

public:
	const string& name() const;  //returns a reference to a constant string
	Type type() const;
	Symbol(const string& name, Type type);
};

std::ostream &operator << (std::ostream &ostr, const Symbol &symbol);


#endif
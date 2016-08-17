#include "symbol.h"

using namespace std;

const string& Symbol::name() const
{
	return _name;
}

Type Symbol::type() const
{
	return _type;
}

Symbol::Symbol(const string& name, Type type)
:_name(name), _type(type)
{
	
}

ostream &operator << (ostream &ostr, const Symbol &symbol)
{
	ostr << "(" << symbol.name() << "," << symbol.type() << ")";
	return ostr;
}
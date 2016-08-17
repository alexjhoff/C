#include "type.h"

using namespace std;

unsigned Type::indirection() const
{
	return _indirection;
}

typeKind Type::kind() const
{
	return _kind;
}

const string& Type::specifier() const
{
	return _specifier;
}

string Type::length() const
{
	return _length;
}

bool Type::operator != (const Type &that) const
{
	return !operator==(that);
}

bool Type::operator == (const Type &that) const
{
	if(_kind != that._kind)
		return false;
	if(_specifier != that._specifier)
		return false;
	if(_indirection != that._indirection)
		return false;
	if(_kind == ARRAY && _length != that._length)
		return false;
	return true;
}

/*
	add ERROR as a kind

	Type::Type()
	:_specifier("-error-"), _indirection(0), _kind(ERROR)
	{
	
	}
*/

Type::Type(const string& specifier, unsigned indirection, typeKind kind, string length)
:_specifier(specifier), _indirection(indirection), _kind(kind), _length(length)
{

}

ostream &operator << (ostream &ostr, const Type &type)
{
	ostr << "(" << type.specifier() << ",";
	ostr << type.indirection() << "," << type.kind() << ")";
	return ostr;
}
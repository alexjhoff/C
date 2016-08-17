#ifndef TYPE_H
#define TYPE_H
#include <string>
#include <ostream>

enum typeKind{SCALAR, FUNCTION, ARRAY};

class Type{
	typedef std::string string;
	string _specifier;
	unsigned _indirection;
	typeKind _kind;
	string _length;

public:
	unsigned indirection() const;
	typeKind kind() const;
	const string& specifier() const;  //returns a reference to a constant string
	string length() const;
	bool operator == (const Type &that) const;
	bool operator != (const Type &that) const;
	Type(const string& specifier, unsigned indirection, typeKind kind, string _length);
};

std::ostream &operator << (std::ostream &ostr, const Type &type);


#endif
#include "egg.hpp"

Egg::Egg(const char *name, const unsigned size /*=1*/)
: name(name)
, size(size)
{}

Egg& Egg::operator++() 
{
	++size;
	return *this;
}

const Egg Egg::operator++(int) 
{
	const Egg temp(*this);
	++(*this);
	return temp;
}

Egg& Egg::operator--() 
{
	--size;
	return *this;
}

const Egg Egg::operator--(int)
{
	const Egg temp(*this);
	--(*this);
	return temp;
}

Egg& Egg::operator+=(const int size) 
{
	this->size += size;
	return *this;
}

Egg& Egg::operator*=(const unsigned size)
{
	this->size *= size;
	return *this;
}

std::ostream& operator<<(std::ostream &os, const Egg &egg) 
{
	os << "Egg's name: " << egg.GetName() << "\t"
		<< "Size: " << egg.GetSize();

	return os;
}

std::istream& operator>>(std::istream &stream, Egg &egg)
{
	return stream >> egg.name >> egg.size;
}
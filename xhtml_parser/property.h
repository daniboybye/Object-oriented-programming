#ifndef __PROPERTY_HEADER_UNCLUDED_
#define __PROPERTY_HEADER_UNCLUDED_

#include <ostream>

namespace fmi {
namespace oop {

class Property {
public:
	Property(const char*);
	Property(const char*&, unsigned long&);
	Property(const Property&);
	Property& operator=(const Property&);
	~Property();

	const char* GetName() const;
	const char* GetValue() const;
	bool GetQuote() const;

private:
	char * name;
	char * value;
	bool dounleOrSingleQuote;

	void Init(const char*&,unsigned long&);
	void Clean();
	void CopyFrom(const Property&);
	void CreateName(const char*&, unsigned long&);
	void CreateValue(const char*&, unsigned long&);
};

std::ostream& operator<<(std::ostream&, const Property&);

} //oop
} //fmi

#include "property.hpp"

#endif //__PROPERT_HEADER_UNCLUDED_
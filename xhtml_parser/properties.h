#ifndef __PROPERTIES_HEADER_UNCLUDED_
#define __PROPERTIES_HEADER_UNCLUDED_

#include "property.h"

namespace fmi {
namespace oop {

class Properties  {
public:
	Properties();
	Properties(const char*);
	Properties(const char**, unsigned);
	~Properties();

	Property& operator[](long);
	Property operator[](long) const;

	unsigned GetPropertiesCount() const;
	void AddProperty(const char*);
	void AddProperty(const char*&, unsigned long&);
	bool DoYouHaveThisValue(const char*) const;

private:
	Property ** properties;
	unsigned count;

	void Clean();
	void Resize();

	Properties(const Properties&);
	void operator=(const Properties&);
};

std::ostream& operator<<(std::ostream&, const Properties&);

} //oop
} //fmi

#include "properties.hpp"

#endif //__PROPERTIES_HEADER_UNCLUDED_
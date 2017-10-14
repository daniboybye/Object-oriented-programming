#ifndef __TAG_CLOSE_WITH_PROPERTIES_HEADER_INCLUDED_
#define __TAG_CLOSE_WITH_PROPERTIES_HEADER_INCLUDED_

#include "tagClose.h"
#include "properties.h"
#include <ostream>

namespace fmi {
namespace oop {

class TagCloseWithProperties : public TagClose {
public:
	TagCloseWithProperties(const char*);
	TagCloseWithProperties(const char*, unsigned);
	virtual~TagCloseWithProperties();

	virtual void Print(std::ostream&, unsigned = 0) const;

	Properties* GetProperties() const;

private:
	Properties * properties;

	TagCloseWithProperties(const TagCloseWithProperties&);
	void operator=(const TagCloseWithProperties&);
};

std::ostream& operator<<(std::ostream&, const TagCloseWithProperties&);

} //oop
} //fmi

#include "tagCloseWithProperties.hpp"

#endif //__TAG_CLOSE_WITH_PROPERTIES_HEADER_INCLUDED_
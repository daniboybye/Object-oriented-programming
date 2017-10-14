#ifndef __TAG_WITH_TAGS_AND_PROPERTIES_HEADER_INCLUDED_
#define __TAG_WITH_TAGS_AND_PROPERTIES_HEADER_INCLUDED_

#include "tagWithTags.h"
#include "properties.h"

namespace fmi {
namespace oop {

class TagWithTagsAndProperties : public TagWithTags {
public:
	TagWithTagsAndProperties(const char*);
	TagWithTagsAndProperties(const char*, unsigned);
	virtual~TagWithTagsAndProperties();

	virtual void Print(std::ostream&, unsigned = 0) const;
	virtual bool Add(Tag*, const char*);

	Properties* GetProperties() const;

private:
	Properties * properties;

	TagWithTagsAndProperties(const TagWithTagsAndProperties&);
	void operator=(const TagWithTagsAndProperties&);
};

}
}

#include "tagWithTagsAndProperties.hpp"

#endif //__TAG_WITH_TAGS_AND_PROPERTIES_HEADER_INCLUDED_
#ifndef __TAG_WITH_TAGS_HEADER_INCLUDED_
#define __TAG_WITH_TAGS_HEADER_INCLUDED_

#include "tag.h"
#include <ostream>

namespace fmi {
namespace oop {

class TagWithTags: public Tag {
public:
	TagWithTags(const char*);
	TagWithTags(const char*, unsigned);
	virtual ~TagWithTags();

	virtual void Print(std::ostream&, unsigned = 0) const;
	virtual void Within(std::ostream&, unsigned = 0) const;
	virtual unsigned Find(const char*) const;
	virtual unsigned Erase(const char*);
	virtual void RoadToWithin(std::ostream&, const char*) const;
	virtual bool Add(Tag*, const char*);
	virtual bool Create(Tag*, const char*);

	void AddTag(Tag*);
	void AddValue(const char*);
	void AddValue(const char*, unsigned);
	const Tag* operator[](long) const;
	unsigned GetTagsCount() const;
	unsigned GetValueCount() const;

	//Tag** GetTags() const;

private:
	Tag ** tags;
	unsigned tagsCount;

	char ** value;
	unsigned valueCount;

	bool * tagOrValue;

	void DeleteTag(const unsigned&);
	void Resize(bool);

	TagWithTags(const TagWithTags&);
	void operator=(const TagWithTags&);
};

} //oop
} //fmi

#include "tagWithTags.hpp"

#endif //__TAG_WITH_TAGS_HEADER_INCLUDED_
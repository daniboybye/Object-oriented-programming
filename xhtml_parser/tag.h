#ifndef __TAG_HEADER_UNCLUDED_
#define __TAG_HEADER_UNCLUDED_

#include <ostream>

namespace fmi {
namespace oop {

class Tag {
public:
	Tag(const char*);
	Tag(const char*,const unsigned&);
	virtual ~Tag();

	virtual void Print(std::ostream&, unsigned = 0) const = 0;
	virtual void Within(std::ostream&, unsigned = 0) const = 0;
	virtual unsigned Find(const char*) const = 0;
	virtual unsigned Erase(const char*) = 0;
	//приема пътя до елементите от потребителя
	virtual void RoadToWithin(std::ostream&, const char*) const = 0;
	virtual bool Add(Tag*, const char*) = 0;
	virtual bool Create(Tag*, const char*) = 0;

	const char* GetName() const;

private:
	char * name;

	Tag(const Tag&);
	void operator=(const Tag&);
};

} //oop
} //fmi

#include "tag.hpp"

#endif //__TAG_HEADER_UNCLUDED_
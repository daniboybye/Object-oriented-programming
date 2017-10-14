#ifndef __TAG_CLOSE_HEADER_INCLUDED_
#define __TAG_CLOSE_HEADER_INCLUDED_

#include "tag.h"
#include <ostream>

namespace fmi {
namespace oop {

class TagClose : public Tag {
public:
	TagClose(const char*);
	TagClose(const char*, unsigned);
	virtual~TagClose();

	virtual void Print(std::ostream&, unsigned = 0) const;
	virtual void Within(std::ostream&, unsigned = 0) const;
	virtual unsigned Find(const char*) const;
	virtual unsigned Erase(const char*);
	virtual void RoadToWithin(std::ostream&, const char*) const;
	virtual bool Add(Tag*, const char*);
	virtual bool Create(Tag*, const char*);

private:
	TagClose(const TagClose&);
	void operator=(const TagClose&);
};

std::ostream& operator<<(std::ostream&, const TagClose&);

}
}

#include "tagClose.hpp"

#endif //__TAG_CLOSE_HEADER_INCLUDED_
#pragma hdrstop
#include "atSections.h"
#include "atSection.h"

namespace ate
{

Sections::Sections()
{}

Sections::~Sections()
{
    for(int i = 0; i < size(); i++)
    {
        delete this->operator[](i);
    }
}

Section* Sections::getSection(int sectionID)
{
    for(int i = 0; i < count(); i++)
    {
        Section* s = at(i);
        if(s->id() == sectionID)
        {
            return s;
        }
    }
    return NULL;
}

Section* Sections::getFirstSection()
{
    mSectionIterator = begin();
    return *(mSectionIterator);
}

Section* Sections::getNextSection()
{
	mSectionIterator++;
    if(mSectionIterator != end())
    {
	    return *(mSectionIterator);
    }
    return NULL;
}

Section* Sections::getPreviousSection()
{
	mSectionIterator--;
    if(mSectionIterator != begin() -1 )
    {
	    return *(mSectionIterator);
    }
    return NULL;
}

Section* Sections::getLastSection()
{
    if(!count())
    {
        return NULL;
    }

    mSectionIterator = end();
	mSectionIterator--;
    return *(mSectionIterator);
}

}

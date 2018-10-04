#pragma hdrstop
#include "atSections.h"
#include "atSection.h"

namespace at
{

Sections::Sections()
{}

Sections::~Sections()
{
    for(int i = 0; i < count(); i++)
    {
        delete mSections[i];
    }
}

Section* Sections::at(unsigned int i)
{
    return mSections[i];
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
    mSectionIterator = mSections.begin();
    return *(mSectionIterator);
}

Section* Sections::getNextSection()
{
	mSectionIterator++;
    if(mSectionIterator != mSections.end())
    {
	    return *(mSectionIterator);
    }
    return NULL;
}

Section* Sections::getPreviousSection()
{
	mSectionIterator--;
    if(mSectionIterator != mSections.begin() -1 )
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

    mSectionIterator = mSections.end();
	mSectionIterator--;
    return *(mSectionIterator);
}

}

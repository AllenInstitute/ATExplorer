#pragma hdrstop
#include "atSections.h"
#include "atSection.h"

namespace at
{

Sections::Sections()
{}

Sections::~Sections()
{}

SectionSP Sections::at(unsigned int i)
{
    return mSections[i];
}

void Sections::clear()
{
	mSections.clear();
}

SectionSP Sections::getSection(int sectionID)
{
    for(int i = 0; i < count(); i++)
    {
        SectionSP s = at(i);
        if(s->id() == sectionID)
        {
            return s;
        }
    }
    return SectionSP();
}

SectionSP Sections::getFirstSection()
{
    if(mSections.size() == 0)
    {
        return SectionSP();
    }
    mSectionIterator = mSections.begin();
    return *(mSectionIterator);
}

SectionSP Sections::getNextSection()
{
    if(mSectionIterator != mSections.end())
    {
		mSectionIterator++;

        if(mSectionIterator == mSections.end())
        {
            return SectionSP();
        }
        else
        {
	    	return *(mSectionIterator);
        }
    }

    return SectionSP();
}

SectionSP Sections::getPreviousSection()
{
	mSectionIterator--;
    if(mSectionIterator != mSections.begin() -1 )
    {
	    return *(mSectionIterator);
    }
    return SectionSP();
}

SectionSP Sections::getLastSection()
{
    if(!count())
    {
        return SectionSP();
    }

    mSectionIterator = mSections.end();
	mSectionIterator--;
    return *(mSectionIterator);
}

}

#pragma hdrstop
#include "atSections.h"

namespace at
{

Sections::Sections(const Ribbon& r)
:
mRibbon(r)
{}

Sections::~Sections()
{
    for(int i = 0; i < size(); i++)
    {
        delete this->operator[](i);
    }
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
    mSectionIterator = end();
	mSectionIterator--;
    return *(mSectionIterator);}



}

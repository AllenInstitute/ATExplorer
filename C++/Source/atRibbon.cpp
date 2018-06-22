#pragma hdrstop
#include "atRibbon.h"

namespace at
{

Ribbon::Ribbon(int id, const string& alias)
:
Sections(*this),
mShortRibbonID(id),
mAlias(alias),
mLongRibbonID("")
{}

Ribbon::~Ribbon()
{

}

bool Ribbon::clear()
{
	for(int i = 0; i < size(); i++)
    {
        delete at(i);
    }
}

void Ribbon::appendSection(Section* sec)
{
    push_back(sec);
}

void Ribbon::allocateSections(int count)
{
    clear();
    resize(count, NULL);

	for(int i = 0; i < count; i++)
    {
        Section* s = new Section(i+1);
        push_back(s);
    }
}

int Ribbon::sectionCount()
{
    return Sections::size();
}

}

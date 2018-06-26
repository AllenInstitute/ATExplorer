#pragma hdrstop
#include "atRibbon.h"
#include "atSection.h"

namespace at
{

Ribbon::Ribbon(int id, const string& alias)
:
Sections(),
mShortRibbonID(id),
mAlias(alias),
mLongRibbonID("")
{}

Ribbon::~Ribbon()
{}

bool Ribbon::clear()
{
	for(uint i = 0; i < size(); i++)
    {
        delete at(i);
    }
    return true;
}

void Ribbon::appendSection(Section* sec)
{
	push_back(sec);
}

int Ribbon::sectionCount()
{
    return Sections::size();
}

}

#pragma hdrstop
#include "atRibbon.h"
#include "atSection.h"
//#include "atExplorerCore.h"
namespace ate
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
	for(unsigned int i = 0; i < size(); i++)
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

void Ribbon::assignLongRibbonID(const string& lid)
{
    mLongRibbonID = lid;
}
}

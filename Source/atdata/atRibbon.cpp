#pragma hdrstop
#include "atRibbon.h"
#include "atSection.h"
//#include "atExplorerCore.h"
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

void Ribbon::removeSections()
{
    Sections::clear();
}

void Ribbon::appendSection(SectionSP sec)
{
	mSections.push_back(sec);
}

int Ribbon::sectionCount()
{
    return mSections.size();
}

void Ribbon::assignLongRibbonID(const string& lid)
{
    mLongRibbonID = lid;
}
}

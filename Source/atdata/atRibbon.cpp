#pragma hdrstop
#include "atRibbon.h"
#include "atSection.h"
//#include "atExplorerCore.h"
//---------------------------------------------------------------------------
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

const string Ribbon::getTypeName() const
{
    return "ribbon";
}

void Ribbon::removeSections()
{
    Sections::clear();
}

string Ribbon::getAlias()
{
	return mAlias;
}

int	Ribbon::getShortRibbonID()
{
	return mShortRibbonID;
}

string Ribbon::getLongRibbonID()
{
	return mLongRibbonID;
}

int Ribbon::getTileCount(const ChannelSP ch)
{
    int count(0);
    for(int i = 0; i < getNumberOfSections(); i++)
    {
        SectionSP s = getSection(i);
        count += s->getNumberOfTiles(ch);
    }
    return count;
}

void Ribbon::appendSection(SectionSP sec)
{
	mSections.push_back(sec);
}

int Ribbon::getNumberOfSections()
{
    return mSections.size();
}

void Ribbon::assignLongRibbonID(const string& lid)
{
    mLongRibbonID = lid;
}
}

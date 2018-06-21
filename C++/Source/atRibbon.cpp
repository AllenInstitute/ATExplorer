#pragma hdrstop
#include "atRibbon.h"

namespace at
{

Ribbon::Ribbon(int id, const string& alias)
:
mShortRibbonID(id),
mAlias(alias),
mLongRibbonID("")
{}

Ribbon::~Ribbon()
{}

int Ribbon::sectionCount()
{
    return Sections::size();
}

}

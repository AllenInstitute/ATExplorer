#pragma hdrstop
#include "atRibbons.h"
#include "atRibbon.h"
//---------------------------------------------------------------------------
namespace at
{


Ribbons::Ribbons()
{}

Ribbons::~Ribbons()
{
    for(int i = 0; i < count(); i++)
    {
        delete mRibbons[i];
    }
}

void Ribbons::append(Ribbon* r)
{
    mRibbons.push_back(r);
}

void Ribbons::clear()
{
//    mRibbonIterator = mRibbons.begin();
//
    for(int i = 0; i < mRibbons.size(); i++)
    {
        delete mRibbons[i];
    }
    mRibbons.clear();
}

Ribbon* Ribbons::getRibbon(int i)
{
	return mRibbons.at(i);
}

Ribbon* Ribbons::operator[](int i)
{
    return mRibbons[i];
}
Ribbon* Ribbons::getFirstRibbon()
{
    mRibbonIterator = mRibbons.begin();
    return *(mRibbonIterator);
}

Ribbon* Ribbons::getNextRibbon()
{
	mRibbonIterator++;
    if(mRibbonIterator != mRibbons.end())
    {
	    return *(mRibbonIterator);
    }
    return NULL;
}

int Ribbons::count()
{
	return mRibbons.size();
}




}

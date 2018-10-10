#pragma hdrstop
#include "atRibbons.h"
#include "atRibbon.h"
//---------------------------------------------------------------------------
namespace at
{


Ribbons::Ribbons()
{}

Ribbons::~Ribbons()
{}

void Ribbons::append(RibbonSP r)
{
    mRibbons.push_back(r);
}

void Ribbons::clear()
{
    mRibbons.clear();
}

RibbonSP Ribbons::getRibbon(int i)
{
	return mRibbons.at(i);
}

RibbonSP Ribbons::operator[](int i)
{
    return mRibbons[i];
}

RibbonSP Ribbons::getFirstRibbon()
{
    mRibbonIterator = mRibbons.begin();
    return *(mRibbonIterator);
}

RibbonSP Ribbons::getNextRibbon()
{
    if(mRibbonIterator != mRibbons.end())
    {
		mRibbonIterator++;
        if(mRibbonIterator == mRibbons.end())
        {
            return RibbonSP();
        }
        else
        {
	    	return *(mRibbonIterator);
        }
    }
    return RibbonSP();
}

int Ribbons::count()
{
	return mRibbons.size();
}




}

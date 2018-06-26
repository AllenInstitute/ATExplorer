#pragma hdrstop
#include "atRibbons.h"
//---------------------------------------------------------------------------
namespace at
{


Ribbons::Ribbons()
{}

Ribbons::~Ribbons()
{
    for(int i = 0; i < size(); i++)
    {
        delete this->operator[](i);
    }
}

Ribbon* Ribbons::getRibbon(int i)
{
	return this->at(i);
}

Ribbon* Ribbons::getFirstRibbon()
{
    mRibbonIterator = begin();
    return *(mRibbonIterator);
}

Ribbon* Ribbons::getNextRibbon()
{
	mRibbonIterator++;
    if(mRibbonIterator != end())
    {
	    return *(mRibbonIterator);
    }
    return NULL;
}

int Ribbons::count()
{
	return this->size();
}




}

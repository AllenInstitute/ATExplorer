#pragma hdrstop
#include "atData.h"
#include "dslLogger.h"
#include "atSections.h"
//---------------------------------------------------------------------------
using namespace dsl;

namespace at
{

ATData::ATData()
{
}

bool ATData::validate()
{
	Log(lDebug) << "Implement in descendants";
}

Ribbons* ATData::getRibbons()
{
    return &mRibbons;
}

Ribbon* ATData::getRibbon(int count)
{
    if(count > 0 && count <= mRibbons.size())
    {
    	return mRibbons[count-1];
    }
    return NULL;
}

Sessions* ATData::getSessions()
{
    return &mSessions;
}

Channels* ATData::getChannels()
{
    return &mChannels;
}

int ATData::getNumberOfRibbons()
{
    return mRibbons.count();
}

int ATData::getNumberOfTiles()
{
    return -1;
}

int ATData::getNumberOfSections()
{
    return -1;
}




}

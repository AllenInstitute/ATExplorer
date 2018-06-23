#pragma hdrstop
#include "atData.h"
#include "dslLogger.h"
#include "atSections.h"
#include "atSession.h"
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
    return false;
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

Channels ATData::getChannels()
{
    //Sum up channels for each session
    Channels chns;
    for(int i = 0; i < mSessions.count(); i++)
    {
        Session* s = mSessions[i];
        chns.append(s->getChannels());
    }

    return chns;
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

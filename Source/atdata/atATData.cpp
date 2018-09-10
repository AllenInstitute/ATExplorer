#pragma hdrstop
#include "atATData.h"
#include "dslLogger.h"
#include "atSections.h"
#include "atSession.h"
//---------------------------------------------------------------------------
using namespace dsl;

namespace ate
{

ATData::ATData(const Path& basePath)
:
mBasePath(basePath)
{
}

Path ATData::getBasePath()
{
    return mBasePath;
}

bool ATData::validate()
{
	Log(lDebug) << "Implement in descendants";
    return false;
}

ATDataFileFormat  ATData::getFileFormat()
{
	return atBase;
}

Ribbons* ATData::getRibbons()
{
    return &mRibbons;
}

Ribbon* ATData::getRibbon(int count)
{
    if(count > 0 && count <= mRibbons.size())
    {
    	return mRibbons[count];
    }
    return NULL;
}

Ribbon* ATData::getFirstRibbon()
{
    return mRibbons.getFirstRibbon();
}

Ribbon* ATData::getNextRibbon()
{
    return mRibbons.getNextRibbon();
}

Sessions* ATData::getSessions()
{
    return &mSessions;
}

Session* ATData::getFirstSession()
{
    return mSessions.getFirstSession();
}

Session* ATData::getNextSession()
{
    return mSessions.getNextSession();
}

Channels* ATData::getChannels(Session* session)
{
    return session->getChannels();
}

Channel* ATData::getFirstChannel(Session* session)
{
    return session->getFirstChannel();
}

Channel* ATData::getNextChannel(Session* session)
{
    return session->getNextChannel();
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

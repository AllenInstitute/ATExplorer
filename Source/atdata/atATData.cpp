#pragma hdrstop
#include "atATData.h"
#include "dslLogger.h"
#include "atSections.h"
#include "atSession.h"
//---------------------------------------------------------------------------
using namespace dsl;

namespace at
{

ATData::ATData(const Path& basePath)
:
mBasePath(basePath)
{
}

ATData::~ATData()
{
    //Use smart pointers to allow worry free deallocation..
}

Path ATData::getBasePath()
{
    return mBasePath;
}

void ATData::reset()
{
    Log(lInfo) << "Resetting ATData - Ribbons";
    mRibbons.clear();

    Log(lInfo) << "Resetting ATData - Sessions";
    mSessions.clear();
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

RibbonSP ATData::getRibbon(int count)
{
    if(count > 0 && count <= mRibbons.count())
    {
    	return mRibbons[count];
    }
    return RibbonSP();
}

RibbonSP ATData::getFirstRibbon()
{
    return mRibbons.getFirstRibbon();
}

RibbonSP ATData::getNextRibbon()
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

StringList ATData::getChannelLabelsForSession(Session* session)
{
    return session->getChannelLabels();
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

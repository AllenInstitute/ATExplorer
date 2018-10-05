#pragma hdrstop
#include "atATData.h"
#include "dslLogger.h"
#include "atSections.h"
#include "atSession.h"
#include "atRibbon.h"
//---------------------------------------------------------------------------
using namespace dsl;

namespace at
{

ATData::ATData(const Path& basePath)
:
mBasePath(basePath)
{}

ATData::~ATData()
{}

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

SessionSP ATData::getFirstSession()
{
    return mSessions.getFirstSession();
}

SessionSP ATData::getNextSession()
{
    return mSessions.getNextSession();
}

StringList ATData::getChannelLabelsForSession(SessionSP session)
{
    return session->getChannelLabels();
}

int ATData::getNumberOfRibbons()
{
    return mRibbons.count();
}

int ATData::getNumberOfTiles()
{
    int tileCount(0);
    for(int r = 0; r < mRibbons.count(); r++)
    {
        RibbonSP ribbon = mRibbons[r];
        for(int ss = 0; ss < ribbon->sectionCount(); ss++)
        {
            SectionSP section = ribbon->getSection(ss);
            tileCount += section->getTotalNumberOfTiles();
        }

    }
    return tileCount;
}

int ATData::getNumberOfSections()
{
    int nrOfSections(0);
    for(int i = 0; i < mRibbons.count(); i++)
    {
        nrOfSections += mRibbons[i]->sectionCount();
    }

    return nrOfSections;
}




}

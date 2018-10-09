#pragma hdrstop
#include "atATData.h"
#include "dslLogger.h"
#include "atSections.h"
#include "atSession.h"
#include "atRibbon.h"
#include <sstream>
//---------------------------------------------------------------------------
using namespace dsl;
using namespace std;

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

string ATData::getInfo()
{
    stringstream s;

    s << "ATData Information Follows =================" << endl;
    //Print some information about ribbons and sections
    s << "Number of Ribbons: "<<this->getNumberOfRibbons() << endl;

    RibbonSP ribbon = this->getFirstRibbon();
    while(ribbon)
    {
        s << "Number of sections in Ribbon \"" << ribbon->getAlias() <<"\" :"<<ribbon->getNumberOfSections() << endl;
        ribbon = this->getNextRibbon();
    }

    //Check Sessions and channels, i.e. actual data
    SessionSP session =  this->getFirstSession();
    while(session)
    {
        s << "\nSession " << session->getLabel() << endl;

        //Get Channels in session
        ChannelSP ch = session->getFirstChannel();
        while(ch)
        {
            s << '\t' << "Channel: " << ch->getLabel() << endl;
            RibbonSP ribbon = this->getFirstRibbon();
            while(ribbon)
            {
                int nrOfSections = ribbon->getNumberOfSections();
                int tileCount = ribbon->getTileCount(ch);
                string ribbonAlias = ribbon->getAlias();

	            s <<  "\t\t\t" << "There are " << tileCount << " tiles in "
                << nrOfSections <<" sections "<< "in Ribbon \"" << ribbonAlias << "\""<< endl;
                ribbon = this->getNextRibbon();
            }
            ch = session->getNextChannel();
        }
        session = this->getNextSession();
    }

    //Total number of tiles??
    long nrOfTiles = this->getNumberOfTiles();
    s << "Total Number of Tiles: " << nrOfTiles << endl;
    s << "==== End of ATData Information" << endl;

    return s.str();
}
void ATData::assignOnPoplateCallbacks(ATDataPopulateCallback onenter, ATDataPopulateCallback onprogress, ATDataPopulateCallback onexit)
{
	onStartingPopulating = onenter;
	onProgressPopulating = onprogress;
	onFinishedPopulating = onexit;
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
        for(int ss = 0; ss < ribbon->getNumberOfSections(); ss++)
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
        nrOfSections += mRibbons[i]->getNumberOfSections();
    }

    return nrOfSections;
}




}

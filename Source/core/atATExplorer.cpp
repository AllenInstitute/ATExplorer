#pragma hdrstop
#include "atATExplorer.h"
#include "dslLogger.h"
#include "dslProperties.h"
#include "dslIniFileProperties.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

ATExplorer gATExplorer;

ATExplorer::ATExplorer()
{
    Log(lInfo) << "Starting up ATExplorer..";
}

ATExplorer::~ATExplorer()
{}

bool ATExplorer::init(IniFile& iniFile)
{
    Log(lDebug4) << "In ATExplorer INIT";

    //Create Property sections for each ini section
    for(int i = 0; i < iniFile.getNumberOfSections(); i++)
    {
        IniSection* iniSection = iniFile.getSection(i);
        if(iniSection && startsWith("RENDER_SERVICE", iniSection->mName))
        {
            //Create a new (empty) inifile section
            PropertiesSP props = PropertiesSP(new IniFileProperties(&iniFile, iniSection->mName));
            append(props);

            createRenderServiceParametersPropertiesInSection(props, iniSection);
            createARenderServiceParametersRecord(props);
        }
    }

    return true;
}

bool ATExplorer::writeProperties()
{
	PropertiesSP p = mINISections.getFirst();
    while(p)
    {
        p->write();
        p = mINISections.getNext();
    }
    return true;
}

void ATExplorer::append(PropertiesSP props)
{
    mINISections.append(props);
}

//Create a new record with data from the PropertySection
bool ATExplorer::createARenderServiceParametersRecord(PropertiesSP sec)
{
	RenderServiceParameters*  rs = new RenderServiceParameters;
    rs->bindToPropertyContainer(sec);
    appendRenderService(rs);
    return true;
}

void ATExplorer::appendRenderService(RenderServiceParameters* rs)
{
    return mRenderServices.append(rs);
}

RenderServiceParameters* ATExplorer::getFirstRenderService()
{
    return mRenderServices.getFirst();
}

RenderServiceParameters* ATExplorer::getNextRenderService()
{
    return mRenderServices.getNext();
}

RenderServiceParameters* ATExplorer::getRenderService(const string& name)
{
	RenderServiceParameters* service = getFirstRenderService();
    while(service)
    {
        if(service->getName() == name)
        {
            return service;
        }
		service = getNextRenderService();
    }
    return NULL;
}

bool ATExplorer::createRenderServiceParametersPropertiesInSection(dsl::PropertiesSP propertiesSection, dsl::IniSection* iniSection)
{
    //We need to know what type a particular property is, this is
    //deduced when setting up (known) datastructures
    //Add RENDER_SERVICE sections
    if(startsWith("RENDER_SERVICE", propertiesSection->getSectionName()))
    {
        //Create a RenderService
		Log(lDebug) << "Found section: " << propertiesSection->getSectionName();

        IniFileProperties* ifp = dynamic_cast<IniFileProperties*>(propertiesSection.get());

        if(!ifp)
        {
            Log(lError) << "syntax error...";
            return false;
        }


        if(iniSection->getKey("NAME"))
        {
            ifp->addStringProperty("NAME", iniSection->getKey("NAME")->mValue);
        }
        else
        {
            Log(lError) << "The NAME record is missing in iniSection: " << iniSection->mName;
        }

        if(iniSection->getKey("HOST"))
        {
            ifp->addStringProperty("HOST", iniSection->getKey("HOST")->mValue);
        }
        else
        {
            Log(lError) << "The HOST record is missing in iniSection: " << iniSection->mName;
        }

        if(iniSection->getKey("PORT"))
        {
            ifp->addIntProperty("PORT", iniSection->getKey("PORT")->asInt());
        }
        else
        {
            Log(lError) << "The PORT record is missing in iniSection: " << iniSection->mName;
        }

        if(iniSection->getKey("PROTOCOL"))
        {
            ifp->addStringProperty("PROTOCOL", iniSection->getKey("PROTOCOL")->mValue);
        }
        else
        {
            Log(lError) << "The PROTOCOL record is missing in iniSection: " << iniSection->mName;
        }

        if(iniSection->getKey("VERSION"))
        {
            ifp->addStringProperty("VERSION", iniSection->getKey("VERSION")->mValue);
        }
        else
        {
            Log(lError) << "The VERSION record is missing in iniSection: " << iniSection->mName;
        }
    }
}



}

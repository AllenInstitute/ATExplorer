#pragma hdrstop
#include "atATExplorer.h"
#include "dslLogger.h"
#include "dslProperties.h"
#include "dslIniFileProperties.h"
#include "dslStringUtils.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

//ATExplorer gATExplorer;

ATExplorer::ATExplorer()
:
Properties(),
Cache(""),
mIniFile(NULL)
{
    Log(lInfo) << "Starting up ATExplorer..";

    //Setup a renderservice

}

ATExplorer::~ATExplorer()
{}

bool ATExplorer::init(IniFile& iniFile)
{
	mIniFile = &iniFile;
	Properties.init(mIniFile);

    setupLogging(Properties.LogFileName.getValue(), Properties.LogLevel.getValue());
    Log(lDebug4) << "In ATExplorer INIT";

    Cache.setBasePath(Properties.LocalCacheFolder);

    //Create Property sections for ini sections
    for(int i = 0; i < mIniFile->getNumberOfSections(); i++)
    {
        IniSection* iniSection = mIniFile->getSection(i);
        if(iniSection && startsWith("RENDER_SERVICE", iniSection->mName))
        {
            //Create a new (empty) inifile section
            PropertiesSP props = PropertiesSP(new IniFileProperties(mIniFile, iniSection->mName));
            createRenderServiceParametersPropertiesInSection(props, iniSection);
            createARenderServiceParametersRecord(props);
        }
    }

    //Setup defaults..
    DefaultRenderService = getFirstRenderService();
    gLogger.setLogLevel(Properties.LogLevel);
    return true;
}

bool ATExplorer::writeProperties()
{
	RenderServiceParameters* rs = mRenderServices.getFirst();
    while(rs && rs->getProperties())
    {
        rs->getProperties()->write();
        rs = mRenderServices.getNext();
    }

    Properties.LogLevel = gLogger.getLogLevel();
    Properties.write();
    return true;
}

//Todo, move this away
void ATExplorer::setupLogging(const string& logFile, LogLevel lvl)
{
	//Get Application folder
    string p(getFilePath(logFile));
	if(!folderExists(p))
	{
		createFolder(p);
	}

	clearFile(logFile);

	gLogger.logToFile(logFile);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = false;
	LogOutput::mUseLogTabs = false;
	gLogger.setLogLevel(lvl);
	Log(lInfo) << "Logger was setup";
}

void ATExplorer::setLogLevel(LogLevel lvl)
{
	gLogger.setLogLevel(lvl);
}

string ATExplorer::getImageMagickPath()
{
    return Properties.ImageMagickPath;
}

RenderServiceParameters* ATExplorer::createRenderService(const string& serviceName)
{
    //Create a new (empty) inifile section
    string iniSection("RENDER_SERVICE_" + serviceName);
    PropertiesSP props = PropertiesSP(new IniFileProperties(mIniFile, iniSection));
    RenderServiceParameters* rs = createARenderServiceParametersRecord(props, serviceName);
    mIniFile->save();
    return rs;
}

bool ATExplorer::removeRenderService(const string& serviceName)
{
    if(mIniFile)
    {
	    mIniFile->deleteSection("RENDER_SERVICE_" + serviceName);
    }

    RenderServiceParameters* rs = getRenderService(serviceName);
    return mRenderServices.remove(rs);
}

//Create a new record with data from the PropertySection
RenderServiceParameters* ATExplorer::createARenderServiceParametersRecord(PropertiesSP sec, const string& name)
{
	RenderServiceParameters*  rs = new RenderServiceParameters;
    rs->bindToPropertyContainer(sec);

    if(name.size())
    {
    	rs->setName(name);
    }

    appendRenderService(rs);
    rs->getProperties()->enableEdits();
    return rs;
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

        string key("NAME");
        if(iniSection->getKey(key))
        {
            ifp->addStringProperty(key, iniSection->getKey(key)->mValue);
        }
        else
        {
            Log(lError) << "The \"" <<key<<"\" record is missing in iniSection: " << iniSection->mName;
        }

        key = "HOST";
        if(iniSection->getKey(key))
        {
            ifp->addStringProperty(key, iniSection->getKey(key)->mValue);
        }
        else
        {
            Log(lError) << "The \"" <<key<<"\" record is missing in iniSection: " << iniSection->mName;
        }

        key = "PORT";
        if(iniSection->getKey(key))
        {
            ifp->addIntProperty(key, iniSection->getKey(key)->asInt());
        }
        else
        {
            Log(lError) << "The \"" <<key<<"\" record is missing in iniSection: " << iniSection->mName;
        }

        key = "PROTOCOL";
        if(iniSection->getKey(key))
        {
            ifp->addStringProperty(key, iniSection->getKey(key)->mValue);
        }
        else
        {
            Log(lError) << "The \"" <<key<<"\" record is missing in iniSection: " << iniSection->mName;
        }

        key = "VERSION";
        if(iniSection->getKey(key))
        {
            ifp->addStringProperty(key, iniSection->getKey(key)->mValue);
        }
        else
        {
            Log(lError) << "The \"" <<key<<"\" record is missing in iniSection: " << iniSection->mName;
        }

        key = "MAX_TILES_TO_RENDER";
        if(iniSection->getKey(key))
        {
            ifp->addIntProperty(key, iniSection->getKey(key)->asInt());
        }
        else
        {
            Log(lError) << "The \"" <<key<<"\" record is missing in iniSection: " << iniSection->mName;
        }
    }
    return true;
}
}

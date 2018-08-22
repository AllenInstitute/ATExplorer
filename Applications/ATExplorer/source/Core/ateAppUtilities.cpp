#pragma hdrstop
#include "ateAppUtilities.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;
namespace at
{

AppUtilities::AppUtilities()
:
ApplicationProperties("ATExplorer", "\\Software\\Allen Institute\\ATExplorer", "0.5.0"),
GeneralProperties(shared_ptr<IniFileProperties>(new IniFileProperties)),
ServerProperties(shared_ptr<IniFileProperties>(new IniFileProperties)),
LocalCacheFolder("",""),
ConnectSSHServersOnStartup(false,""),
LastSelectedSettingSection("",""),
LogLevel(lAny),
BottomPanelHeight(205),
CurrentProject(""),
CurrentOwner(""),
CurrentStack("")
{
}

AppUtilities::~AppUtilities()
{
    Log(lInfo) << "In ATExplorers AppUtilities destructor..";
}

bool AppUtilities::setupIniParameters()
{
	GeneralProperties->setIniFile(&getIniFile());
	GeneralProperties->setSection("General");


	GeneralProperties->add((BaseProperty*)  &BottomPanelHeight.setup( 	            "HEIGHT_OF_BOTTOM_PANEL",    	    205));
	GeneralProperties->add((BaseProperty*)  &LogLevel.setup( 	                  	"LOG_LEVEL",    	                lAny));
	GeneralProperties->add((BaseProperty*)  &LocalCacheFolder.setup(				"LOCAL_CACHE_FOLDER",  				"C:\\ImageCache"));

    GeneralProperties->add((BaseProperty*)  &CurrentOwner.setup(		       		"OWNER", 		                    ""));
    GeneralProperties->add((BaseProperty*)  &CurrentProject.setup(	    			"PROJECT", 		                    ""));
    GeneralProperties->add((BaseProperty*)  &CurrentStack.setup(	          		"STACK_NAME", 	                    ""));

    return true;
}

}

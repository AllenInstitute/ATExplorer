#include <vcl.h>
#pragma hdrstop
#include "ateAppUtilities.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

using namespace dsl;
AppUtilities::AppUtilities()
:
ApplicationProperties("ATExplorer", "\\Software\\Allen Institute\\ATExplorer", "0.5.0"),
GeneralProperties(shared_ptr<IniFileProperties>(new IniFileProperties)),
ServerProperties(shared_ptr<IniFileProperties>(new IniFileProperties)),
LocalCacheFolder("",""),
ConnectSSHServersOnStartup(false,""),
LastSelectedSettingsSection("",""),
LogLevel(lAny),
BottomPanelHeight(205),
//CurrentProject(""),
//CurrentOwner(""),
//CurrentStack(""),
BaseURL(""),
ProjectPanelWidth(100),
LastOpenedProject("")
{
    append(GeneralProperties);
    append(ServerProperties);
}

AppUtilities::~AppUtilities()
{
    Log(lInfo) << "In ATExplorers AppUtilities destructor..";
}

bool AppUtilities::setupIniParameters()
{
	GeneralProperties->setIniFile(&getIniFile());
	ServerProperties->setIniFile(&getIniFile());
	GeneralProperties->setSection("General");
    ServerProperties->setSection("Remote SSH Server");

	GeneralProperties->add((BaseProperty*)  &BottomPanelHeight.setup( 	            "HEIGHT_OF_BOTTOM_PANEL",    	    205));
    GeneralProperties->add((BaseProperty*)  &ProjectPanelWidth.setup( 	            "PROJECT_PANEL_WIDTH",    	   		205));

	GeneralProperties->add((BaseProperty*)  &LogLevel.setup( 	                  	"LOG_LEVEL",    	                lAny));
	GeneralProperties->add((BaseProperty*)  &LocalCacheFolder.setup(				"LOCAL_CACHE_FOLDER",  				"C:\\ImageCache"));
	GeneralProperties->add((BaseProperty*)  &LastSelectedSettingsSection.setup(	  	"LAST_SELECTED_SETTINGS_SECTION",	""));

    //This should be part of a project
    GeneralProperties->add((BaseProperty*)  &BaseURL.setup(   						"BASE_URL",  						"http://ibs-forrestc-ux1.corp.alleninstitute.org"));
//    GeneralProperties->add((BaseProperty*)  &CurrentOwner.setup(		       		"OWNER", 		                    ""));
//    GeneralProperties->add((BaseProperty*)  &CurrentProject.setup(	    			"PROJECT", 		                    ""));
//    GeneralProperties->add((BaseProperty*)  &CurrentStack.setup(	          		"STACK_NAME", 	                    ""));

	GeneralProperties->add((BaseProperty*)  &ConnectSSHServersOnStartup.setup(   	"CONNECT_SERVERS_ON_STARTUP",  		false));
	GeneralProperties->add((BaseProperty*)  &LastOpenedProject.setup(   			"LAST_OPENED_PROJECT",  			""));

    return true;
}

}

#include <vcl.h>
#pragma hdrstop
#include "ATExplorerUIProperties.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

ATExplorerUIProperties gUIProperties;

using namespace dsl;
ATExplorerUIProperties::ATExplorerUIProperties()
:
ApplicationProperties("ATExplorer", "\\Software\\Allen Institute\\ATExplorer", "0.5.0"),
GeneralProperties(shared_ptr<IniFileProperties>(new IniFileProperties)),
LastSelectedSettingsSection("",""),
BottomPanelHeight(205),
ProjectPanelWidth(100),
LastOpenedProject("")
{
    append(GeneralProperties);
}

ATExplorerUIProperties::~ATExplorerUIProperties()
{
    Log(lInfo) << "In ATExplorers ATExplorerUIProperties destructor..";
}

bool ATExplorerUIProperties::setupGeneralProperties()
{
	GeneralProperties->setIniFile(&mIniFile);
	GeneralProperties->setSectionName("General");

	GeneralProperties->add((BaseProperty*)  &BottomPanelHeight.setup( 	            "HEIGHT_OF_BOTTOM_PANEL",    	    205));
    GeneralProperties->add((BaseProperty*)  &ProjectPanelWidth.setup( 	            "PROJECT_PANEL_WIDTH",    	   		205));
//	GeneralProperties->add((BaseProperty*)  &LocalCacheFolder.setup(				"LOCAL_CACHE_FOLDER",  				"C:\\ImageCache"));
	GeneralProperties->add((BaseProperty*)  &LastSelectedSettingsSection.setup(	  	"LAST_SELECTED_SETTINGS_SECTION",	""));

    //This should be part of a project
//    GeneralProperties->add((BaseProperty*)  &ImageMagickPath.setup(   				"IMAGE_MAGICK_PATH",  				"C:\\"));
	GeneralProperties->add((BaseProperty*)  &LastOpenedProject.setup(   			"LAST_OPENED_PROJECT",  			""));

    return true;
}

}

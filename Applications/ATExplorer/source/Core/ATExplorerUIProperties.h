#ifndef ATExplorerUIPropertiesH
#define ATExplorerUIPropertiesH
#include "dslApplicationProperties.h"
#include "dslProperty.h"
#include "dslIniFileProperties.h"
#include "dslSharedPointer.h"
#include "dslLogLevel.h"
//---------------------------------------------------------------------------
namespace at
{

using dsl::Property;
using dsl::IniFileProperties;
using dsl::LogLevel;

class PACKAGE ATExplorerUIProperties : public dsl::ApplicationProperties
{
    public:
                                            ATExplorerUIProperties();
                                            ~ATExplorerUIProperties();
        bool                                setupGeneralProperties();

                                            //General Properties
        shared_ptr<IniFileProperties> 		GeneralProperties;

                                            //Automatically managed properties ============================
        Property<string>                	LocalCacheFolder;
        Property<int>	                    BottomPanelHeight;
        Property<int>	                    ProjectPanelWidth;

                                            //!Used to open up the Settings Treeview where it was last time
        Property<string>                	LastSelectedSettingsSection;
        Property<string>                	ImageMagickPath;

                                            //These properties may be exposed for change in the UI ========
        Property<string>	 		        LastOpenedProject;

};

//This creates a global ATExplorerUIProperties object
extern PACKAGE ATExplorerUIProperties gUIProperties;

}
#endif

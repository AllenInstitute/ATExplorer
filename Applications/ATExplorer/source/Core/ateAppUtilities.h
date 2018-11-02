#ifndef ateAppUtilitiesH
#define ateAppUtilitiesH
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

class PACKAGE AppUtilities : public dsl::ApplicationProperties
{
    public:
                                            AppUtilities();
                                            ~AppUtilities();
        bool                                setupIniParameters();

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
        Property<bool>	                	ConnectSSHServersOnStartup;
        Property<LogLevel>	 	           	LogLevel;
        Property<string>	 		        BaseURL;
        Property<string>	 		        LastOpenedProject;
};

//This creates a global AppUtilities object
extern PACKAGE AppUtilities gAU;

}
#endif

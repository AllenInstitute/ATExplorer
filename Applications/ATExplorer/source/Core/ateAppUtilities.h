#ifndef ateAppUtilitiesH
#define ateAppUtilitiesH
#include "dslApplicationProperties.h"
#include "atATObject.h"
#include "dslProperty.h"
#include "dslIniFileProperties.h"
#include "dslSharedPointer.h"
#include "dslLogLevel.h"
//---------------------------------------------------------------------------
namespace at
{

using dsl::Property;
using dsl::IniFileProperties;
using dsl::shared_ptr;
using dsl::LogLevel;

class PACKAGE AppUtilities : public dsl::ApplicationProperties
{

        public:
                            					AppUtilities();
                            					~AppUtilities();
            bool                                setupIniParameters();


                                                //General Properties
	        shared_ptr<IniFileProperties> 		GeneralProperties;
	        shared_ptr<IniFileProperties>       ServerProperties;


                                                //Automatically managed properties ============================
        	Property<string>                	LocalCacheFolder;
        	Property<int>	                    BottomPanelHeight;

                                                //!Used to open up the Settings Treeview where it was last time
          	Property<string>                	LastSelectedSettingSection;

                                                //These properties may be exposed for change in the UI ========
        	Property<bool>	                	ConnectSSHServersOnStartup;
			Property<LogLevel>	 	           	LogLevel;
            Property<string>	 		        CurrentProject;
            Property<string>	 		        CurrentOwner;
            Property<string>	 		        CurrentStack;
            Property<string>	 		        BaseURL;


        protected:

        private:

};


}
#endif

#ifndef atATExplorerPropertiesH
#define atATExplorerPropertiesH
#include <list>
#include <System.hpp>
#include "dslObject.h"
#include "dslProperties.h"
#include "dslIniFile.h"
#include "dslSharedPointer.h"
#include "dslIniFileProperties.h"
//#include "dslRegistryProperties.h"
#include "atExplorerObject.h"
#include "dslLogLevel.h"
//---------------------------------------------------------------------------

namespace at
{
using dsl::Properties;
using dsl::IniFileProperties;
using dsl::IniFile;
using dsl::Property;
using dsl::PropertiesSP;
using dsl::LogLevel;
using std::list;
using std::string;
using dsl::BaseProperty;

class ATE_CORE ATExplorerProperties : public ExplorerObject
{
    public:
                                                                ATExplorerProperties();
                                                                ~ATExplorerProperties();
		void 					                                init(IniFile* iniFile);

                                                                //!ATExplorer properties
		Property<string>                                        LogFileName;
		Property<string>                                        LogFileLocation;
        Property<LogLevel>	 	           						LogLevel;

                                                                //Save default to use containers
        Property<string>                                        DefaultRenderPythonContainer;
        Property<string>                                        DefaultRenderServiceContainer;
        Property<string>                                        DefaultATModulesContainer;
        Property<string>                                        DefaultRenderServiceHost;
		Property<string>                                        ImageMagickPath;
		
        void													read();
		void													write();
        PropertiesSP                                  			getSection(const string& sec);
        shared_ptr<IniFileProperties>                           createNewINISection(const string& secName);
        void                                                    append(PropertiesSP props);

        PropertiesSP                                            getFirstSection() const;
        PropertiesSP                                            getNextSection();
        PropertiesSP                                            getCurrentSection();

        bool                                                    hasChanges();
		string			                                        getLogFileNameAndPath();

        IniFile*                                                getIniFile();
        bool                                					saveIniFile();
        BaseProperty*                                           getProperty(const string& name, const string& sectionName = dsl::gEmptyString);

	protected:
		IniFile*                 						        mIniFile;

                                                    	        //Each item holds a container of related properties
        mutable list<PropertiesSP >   							mSections;
        mutable list<PropertiesSP >::iterator    				mSectionIterator;
};
}
#endif

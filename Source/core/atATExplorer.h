#ifndef atATExplorerH
#define atATExplorerH
#include "atExplorerObject.h"
#include "atGenericListOfPointers.h"
#include "atRenderServiceParameters.h"
#include "atDockerContainer.h"
#include "dslIniFile.h"
#include "dslProperties.h"
#include "atATExplorerProperties.h"
#include "atRenderClient.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::IniFile;
using dsl::IniSection;

//!The ATExplorer class is a composite superclass, encapsulating datastructures and functionality
class ATE_CORE ATExplorer : public ExplorerObject
{
    public:
                                                ATExplorer();
                                                ~ATExplorer();
        bool                                    init(IniFile& iniFile);
        bool                                    writeProperties();
	    void									setupLogging(const string& logFileName, LogLevel lvl);
        void                                    setLogLevel(LogLevel lvl);

                                                //Renderservices
        void                                    appendRenderService(RenderServiceParameters*  rs);
        RenderServiceParameters*                getFirstRenderService();
        RenderServiceParameters*                getNextRenderService();
        RenderServiceParameters*                getRenderService(const string& name);
        RenderServiceParameters*                createRenderService(const string& serviceName);
        bool                                    removeRenderService(const string& serviceName);
		RenderServiceParameters*                DefaultRenderService;

                                                //Docker containers
        void                                    appendDockerContainer(DockerContainer*  rs);
        DockerContainer*                        getFirstDockerContainer();
        DockerContainer*                        getNextDockerContainer();
        DockerContainer*                        getDockerContainer(const string& name);
        DockerContainer*                        createDockerContainer(const string& serviceName);
        bool                                    removeDockerContainer(const string& serviceName);

                                                //Default docker containers
        DockerContainer*                        DefaultRenderPythonApps;
        DockerContainer*                        DefaultATModules;
        DockerContainer*                        DefaultRenderServiceContainer;

        string                                  getImageMagickPath();

        ATExplorerProperties                    Properties;

		RenderClient                            RenderClient;
    protected:


    	ListOfPointers< RenderServiceParameters* > 		mRenderServices;

		RenderServiceParameters*				createARenderServiceParametersRecord(dsl::PropertiesSP sec, const string& name = dsl::gEmptyString);
		bool									createRenderServiceParametersPropertiesInSection(dsl::PropertiesSP props, IniSection* sec);

    	ListOfPointers< DockerContainer* > 	 	mDockerContainers;
		DockerContainer*						createADockerContainerRecord(dsl::PropertiesSP sec, const string& name = dsl::gEmptyString);
		bool									createDockerContainerPropertiesInSection(dsl::PropertiesSP props, IniSection* sec);

        IniFile*                                mIniFile;
};

//extern ATE_CORE ATExplorer gATExplorer;
}

#endif
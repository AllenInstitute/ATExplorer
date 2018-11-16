#ifndef atATExplorerH
#define atATExplorerH
#include "atExplorerObject.h"
#include "atGenericList.h"
#include "atRenderServiceParameters.h"
#include "atDockerContainer.h"
#include "dslIniFile.h"
#include "dslProperties.h"
#include "atATExplorerProperties.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::IniFile;
using dsl::IniSection;
class ATE_CORE ATExplorer : public ExplorerObject
{
    public:
                                                ATExplorer();
                                                ~ATExplorer();
        bool                                    init(IniFile& iniFile);
        bool                                    writeProperties();
	    void									setupLogging(const string& logFileName, LogLevel lvl);

                                                //Renderservices
        void                                    appendRenderService(RenderServiceParameters*  rs);
        RenderServiceParameters*                getFirstRenderService();
        RenderServiceParameters*                getNextRenderService();
        RenderServiceParameters*                getRenderService(const string& name);
        RenderServiceParameters*                createRenderService(const string& serviceName);
        bool                                    removeRenderService(const string& serviceName);

                                                //Docker containers
        void                                    appendDockerContainer(DockerContainer*  rs);
        DockerContainer*                        getFirstDockerContainer();
        DockerContainer*                        getNextDockerContainer();
        DockerContainer*                        getDockerContainer(const string& name);
        DockerContainer*                        createDockerContainer(const string& serviceName);
        bool                                    removeDockerContainer(const string& serviceName);

                                                //Default docker containers
        DockerContainer*                        mRenderPythonApps;
        DockerContainer*                        mATModules;
        DockerContainer*                        mRenderService;

        ATExplorerProperties                    Properties;

    protected:
    	List< RenderServiceParameters* > 		mRenderServices;

		RenderServiceParameters*				createARenderServiceParametersRecord(dsl::PropertiesSP sec, const string& name = dsl::gEmptyString);
		bool									createRenderServiceParametersPropertiesInSection(dsl::PropertiesSP props, IniSection* sec);

    	List< DockerContainer* > 				mDockerContainers;
		DockerContainer*						createADockerContainerRecord(dsl::PropertiesSP sec, const string& name = dsl::gEmptyString);
		bool									createDockerContainerPropertiesInSection(dsl::PropertiesSP props, IniSection* sec);

        IniFile*                                mIniFile;

};

extern ATE_CORE ATExplorer gATExplorer;
}


#endif

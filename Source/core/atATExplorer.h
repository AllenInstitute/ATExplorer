#ifndef atATExplorerH
#define atATExplorerH
#include "atExplorerObject.h"
#include "atGenericListOfPointers.h"
#include "atRenderServiceParameters.h"
#include "dslIniFile.h"
#include "dslProperties.h"
#include "atATExplorerProperties.h"
#include "atRenderClient.h"
#include "atRenderLocalCache.h"
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
        bool                                                init(IniFile& iniFile);
        bool                                                writeProperties();
	    void									            setupLogging(const string& logFileName, LogLevel lvl);
        void                                                setLogLevel(LogLevel lvl);

                                                            //Renderservices
        void                                                appendRenderService(RenderServiceParameters*  rs);
        RenderServiceParameters*                            getFirstRenderService();
        RenderServiceParameters*                            getNextRenderService();
        RenderServiceParameters*                            getRenderService(const string& name);
        RenderServiceParameters*                            createRenderService(const string& serviceName);
        bool                                                removeRenderService(const string& serviceName);
		RenderServiceParameters*                            DefaultRenderService;

        string                                              getImageMagickPath();
        ATExplorerProperties                                Properties;
		RenderClient                                        RenderClient;
        RenderLocalCache                                    Cache;

    protected:
        IniFile*                                            mIniFile;
    	ListOfPointers< RenderServiceParameters* > 			mRenderServices;

		RenderServiceParameters*				            createARenderServiceParametersRecord(dsl::PropertiesSP sec, const string& name = dsl::gEmptyString);
		bool									            createRenderServiceParametersPropertiesInSection(dsl::PropertiesSP props, IniSection* sec);
};

}

#endif
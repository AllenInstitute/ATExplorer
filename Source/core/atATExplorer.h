#ifndef atATExplorerH
#define atATExplorerH
#include "atExplorerObject.h"
#include "atGenericList.h"
#include "atRenderServiceParameters.h"
#include "dslIniFile.h"
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

        void                                    appendRenderService(RenderServiceParameters*  rs);
        RenderServiceParameters*                getFirstRenderService();
        RenderServiceParameters*                getNextRenderService();
        RenderServiceParameters*                getRenderService(const string& name);
        RenderServiceParameters*                createRenderService(const string& serviceName);
        bool                                    removeRenderService(const string& serviceName);

    protected:
    	List< RenderServiceParameters* > 		mRenderServices;
		RenderServiceParameters*				createARenderServiceParametersRecord(dsl::PropertiesSP sec, const string& name = dsl::gEmptyString);
		bool									createRenderServiceParametersPropertiesInSection(dsl::PropertiesSP props, IniSection* sec);

        IniFile*                                mIniFile;
};

extern ATE_CORE ATExplorer gATExplorer;
}


#endif

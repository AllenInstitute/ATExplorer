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


    protected:
    	List< RenderServiceParameters* > 		mRenderServices;
		bool									createARenderServiceParametersRecord(dsl::PropertiesSP sec);
		bool									createRenderServiceParametersPropertiesInSection(dsl::PropertiesSP props, IniSection* sec);
		void                                    append(PropertiesSP props);

        										//Each item holds a container of related properties
        List< PropertiesSP >   			  		mINISections;

};

extern ATE_CORE ATExplorer gATExplorer;
}


#endif

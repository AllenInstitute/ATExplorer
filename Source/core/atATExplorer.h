#ifndef atATExplorerH
#define atATExplorerH
#include "atExplorerObject.h"
#include "atGenericList.h"
#include "atRenderServiceParameters.h"
//---------------------------------------------------------------------------

namespace at
{

class ATE_CORE ATExplorer : public ExplorerObject
{
    public:
                                                ATExplorer();
                                                ~ATExplorer();

        void                                    appendRenderService(RenderServiceParameters  rs);
        RenderServiceParameters                 getFirstRenderService();
        RenderServiceParameters                 getNextRenderService();

    protected:
    	List< RenderServiceParameters > 		mRenderServices;
};

ATE_CORE ATExplorer gATExplorer;
}


#endif

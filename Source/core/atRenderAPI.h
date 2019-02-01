#ifndef atRenderAPIH
#define atRenderAPIH
#include "atExplorerObject.h"
//---------------------------------------------------------------------------
namespace at
{
class RESTResponse;
class RESTRequest;
class RenderClient;

//!Baseclass for the RenderAPI. This could be done by composition, but inheritance is easier to use.
class ATE_CORE RenderAPI : public ExplorerObject
{
    public:
                        			RenderAPI(const string& name, RenderClient& rc);
                        			~RenderAPI();
        string                      getName();
        virtual RESTResponse*       execute(RESTRequest& r);

    protected:
        string                      mAPIName;
		RenderClient&				mRC;

};

}

#endif

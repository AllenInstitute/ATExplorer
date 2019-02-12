#ifndef atRenderStackDataAPIH
#define atRenderStackDataAPIH
#include "atExplorerObject.h"
#include "dslStringList.h"
#include "atGenericList.h"
#include "atRenderAPI.h"
//---------------------------------------------------------------------------


namespace at
{

using dsl::StringList;


class RESTResponse;
class RESTRequest;
class ATE_CORE RenderStackDataAPI : public RenderAPI
{

    public:
                        			                RenderStackDataAPI(RenderClient& rc);
                        			                ~RenderStackDataAPI();

                                                    //StackData API's
		StringList						            getOwners();
        StringList						            getProjectsForOwner(const string& o);
        StringList						            getStacksForProject(const string& o, const string& p);
        RESTResponse* 								execute(RESTRequest& request);


    protected:

        
};

}


#endif

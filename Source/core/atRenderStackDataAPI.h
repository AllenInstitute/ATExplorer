#ifndef atRenderStackDataAPIH
#define atRenderStackDataAPIH
#include "atExplorerObject.h"
#include "dslStringList.h"
#include "atRenderAPI.h"
#include <vector>
#include "atRenderProject.h"
//---------------------------------------------------------------------------

namespace at
{

using std::vector;
using dsl::StringList;
using at::RenderProject;

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
        vector<int>						            getZsForStack(const RenderProject& p);
        vector<int>						            getZsForStack(const string& o, const string& p, const string& stack);
        RESTResponse* 								execute(RESTRequest& request);

    protected:

};

}

#endif

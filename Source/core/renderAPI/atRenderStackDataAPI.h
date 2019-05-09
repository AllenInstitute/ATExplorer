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
        StringList						            getZsForStack(const RenderProject& p);
        StringList						            getZsForStack(const string& o, const string& p, const string& stack);
		RegionOfInterest 							getLayerBoundsForZ(const RenderProject& rp, int z);
	    StringList									getChannelsInStack(const string& o, const string& p, const string& stack);
		StringList 									getChannelsInSelectedStack(const RenderProject& p);
        bool                                        deleteProject(const string& o, const string& p);
        bool                                        deleteStack(const string& o, const string& p, const string& s);

        RESTResponse* 								execute(RESTRequest& request);

    protected:

};

}

#endif

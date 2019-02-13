#ifndef atRenderPointMatchAPIH
#define atRenderPointMatchAPIH
#include "atExplorerObject.h"
#include "dslStringList.h"
#include "atGenericListOfPointers.h"
#include "atRenderAPI.h"
#include "atGenericListOfObjects.h"
#include "pointMatches/atPointMatch.h"
//---------------------------------------------------------------------------


namespace at
{

using dsl::StringList;
class PointMatchCollection;
class RenderClient;
class ATE_CORE RenderPointMatchAPI : public RenderAPI
{

    public:
                        			                RenderPointMatchAPI(RenderClient& rc);
                        			                ~RenderPointMatchAPI();

		RESTResponse* 								execute(RESTRequest& request);
                                                    
                                                    //Pointmatch API's
		StringList									getPointMatchCollectionOwners();
		StringList									getPointMatchCollectionNamesForOwner(const string& o);
		ListOfPointers<PointMatchCollection*>  		getPointMatchCollectionsForOwner(const string& o);
		StringList									getPointMatchGroupIDs(const string& o, const string& matchCollection);
		StringList									getPPointMatchGroupIDs(const string& o, const string& matchCollection);
		StringList									getQPointMatchGroupIDs(const string& o, const string& matchCollection);
		ListOfObjects<PointMatch> 		   			getPQMatches(const string& o, const string& matchCollection, const string& pGroup, const string& qGroup);
        bool                                        deletePointMatchCollection(const string& owner, const string& matchCollection);


    protected:


};

}


#endif

#ifndef atRESTRequestH
#define atRESTRequestH
#include "atExplorerObject.h"
#include "dslStringList.h"
#include "atRestClient.h"
#include <sstream>
//---------------------------------------------------------------------------

namespace at
{

using dsl::StringList;
using std::stringstream;

enum RequestMethod {rmPost, rmGet, rmUndefined};
//!Abstract base class for REST requests
class ATE_CORE RESTRequest : public ExplorerObject
{

    public:
                                    RESTRequest(const string& baseURL);
        virtual                     ~RESTRequest();
        virtual RequestMethod       getMethod(){return mRequestMethod;}
        string                      getRequestURL();


    protected:
        RequestMethod               mRequestMethod;
        string                      mBaseURL;
    	stringstream 	            mRequestURL;


};

}


#endif

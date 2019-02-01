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

enum RequestMethod {rmPost, rmGet, rmDelete, rmUndefined};
//!Abstract base class for REST requests
class ATE_CORE RESTRequest : public ExplorerObject
{

    public:
                                    RESTRequest(const string& baseURL, RequestMethod rm = rmUndefined, ExplorerObject* o = NULL);
        virtual                     ~RESTRequest();

        void                        addParameter(const string& name, const string& value);
        void                        addSegment(const string& seg);
        virtual RequestMethod       getMethod(){return mRequestMethod;}
        string                      getRequestURL();
        ExplorerObject*             getRequestorObject(){return mRequestorObject;}

    protected:
        RequestMethod               mRequestMethod;
        string                      mBaseURL;
    	stringstream 	            mRequestURL;

                                	//!The requester object (API) making the request
        ExplorerObject*             mRequestorObject;
};

}

#endif

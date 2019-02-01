#ifndef atRESTClientH
#define atRESTClientH
#include "atExplorerObject.h"
#include "atRESTServiceParameters.h"
#include "atRESTResponse.h"
#include <IdHTTP.hpp>
#include <string>
//---------------------------------------------------------------------------

namespace at
{

using std::string;
class RESTRequest;

//!Abstract class..
class ATE_CORE RESTClient : public ExplorerObject
{
    public:
                        						RESTClient(shared_ptr<Idhttp::TIdHTTP> client = shared_ptr<Idhttp::TIdHTTP>(), const string& host = "localhost");
    	virtual            						~RESTClient();
        string                                  getBaseURL();
        int 					                executeRequest(RESTRequest& request, string& response);
        int                                     getLastHTTPResponseCode(){return mLastHTTPResponseCode;}

    protected:
		shared_ptr<Idhttp::TIdHTTP>     		mHTTPClient;
    	RESTServiceParameters*                  mServiceParameters;
        int                                     mLastHTTPResponseCode;

        virtual void                            createRESTServiceParameters(const string& host) = 0;

};

}

#endif

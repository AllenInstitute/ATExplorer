#pragma hdrstop
#include "atRESTClient.h"
#include "atRESTRequest.h"
#include <IdHTTP.hpp>
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------

namespace at
{
using namespace std;
using namespace dsl;


RESTClient::RESTClient(shared_ptr<Idhttp::TIdHTTP> client, const string& host)
:
mHTTPClient(client)
{}

RESTClient::~RESTClient()
{}

string RESTClient::getBaseURL()
{
    if(mServiceParameters)
	{
        return mServiceParameters->getBaseURL();
    }
    return "";
}

string RESTClient::executeRequest(RESTRequest& request)
{
    //Synchronous
	unique_ptr<TStringStream> zstrings (new TStringStream);

    switch(request.getMethod())
	{
        case rmPost:
        break;

		case rmGet:
		    mHTTPClient->Get(request.getRequestURL().c_str(), zstrings.get());
        break;

        default:
        break;
    }


    if(mHTTPClient->ResponseCode == 200)
    {
        string s = stdstr(zstrings->DataString);
        return s;
    }

    return "";
}

}

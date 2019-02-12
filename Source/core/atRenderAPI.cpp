#pragma hdrstop
#include "atRenderAPI.h"
#include "atRenderClient.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;
RenderAPI::RenderAPI(const string& name, RenderClient& rc)
:
mAPIName(name),
mRC(rc)
{}

RenderAPI::~RenderAPI()
{}

string RenderAPI::getName()
{
	mAPIName;
}

RESTResponse* RenderAPI::execute(RESTRequest& request)
{
    //Create a response object
    try
    {
        string result;
        int responseCode = mRC.executeRequest(request, result);
        Log(lDebug) << "HTTP Response code: " << responseCode;
        return new RESTResponse(result, responseCode);
    }
    catch(...)
    {
        Log(lError) << "Uncaught error in executing http request. Response code: " << mRC.getLastHTTPResponseCode();
        return NULL;
    }
}

}


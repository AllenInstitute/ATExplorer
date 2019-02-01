#pragma hdrstop
#include "atRenderStackDataAPI.h"
#include "atRenderClient.h"
#include "atPointMatchCollection.h"
#include "atRESTRequest.h"
#include "atRESTResponse.h"
#include "renderAPI/atGetOwnersResponse.h"
#include "atJSONParser.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;
RenderStackDataAPI::RenderStackDataAPI(RenderClient& rc)
:
RenderAPI("StackDataAPI", rc)
{}

RenderStackDataAPI::~RenderStackDataAPI()
{}

RESTResponse* RenderStackDataAPI::execute(RESTRequest& request)
{
    //Create a response object
    string r;
    int responseCode = mRC.executeRequest(request, r);
    Log(lDebug) << "HTTP Response code: " << responseCode;
    return new RESTResponse(r, responseCode);
}

StringList RenderStackDataAPI::getOwners()
{
    RESTRequest request(mRC.getBaseURL(), rmGet, this);
    request.addSegment("owners");

    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));
    return (response) ?	response->getAsStringList() : StringList();
}

StringList RenderStackDataAPI::getProjectsForOwner(const string& o)
{
    RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addParameter("owner", o);
    request.addSegment("projects");

    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));

    return (response) ?	response->getAsStringList() : StringList();
}

StringList RenderStackDataAPI::getStacksForProject(const string& o, const string& p)
{
    RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addParameter("owner", o);
    request.addParameter("project", p);
    request.addSegment("stackIds");

    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));

    JSONParser parser(response->getContent());

    //Check how many records
    StringList list;
    for(int i = 0 ; i < parser.getNumberOfTokens(); i++)
    {
    	const JSONToken* t = parser.getToken(i);
        if(t && (t->type == JSMN_OBJECT))
        {
            string val = parser.getStringValueInObject(t, "stack");
            list.append(val);
        }
    }

    return list;
}


}


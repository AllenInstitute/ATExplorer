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

StringList	RenderStackDataAPI::getZsForStack(const RenderProject& p)
{
    return getZsForStack(p.getProjectOwner(), p.getRenderProjectName(), p.getSelectedStackName());
}

StringList RenderStackDataAPI::getZsForStack(const string& o, const string& p, const string& stack)
{
    RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addParameter("owner", o);
    request.addParameter("project", p);
    request.addParameter("stack", stack);
    request.addSegment("zValues");

    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));

    JSONParser parser(response->getContent());
	StringList zs(parser.getStringList());
    return zs;
}
StringList RenderStackDataAPI::getChannelsInSelectedStack(const RenderProject& p)
{
    return RenderStackDataAPI::getChannelsInStack(p.getProjectOwner(), p.getRenderProjectName(), p.getSelectedStackName());
}

bool RenderStackDataAPI::deleteProject(const string& o, const string& p)
{
    //This involves deleting all stacks first
    StringList stacks =  getStacksForProject(o, p);
    for(int i = 0; i < stacks.count(); i++)
    {
        if(deleteStack(o, p, stacks[i]))
        {
	        Log(lInfo) << "Deleted stack: " << stacks[i];
        }
        else
        {
	        Log(lWarning) << "Failed to delete stack: " << stacks[i];
        }
    }
    return true;
}


bool RenderStackDataAPI::deleteStack(const string& o, const string& p, const string& s)
{
	RESTRequest request(mRC.getBaseURL(), rmDelete);
    request.addParameter("owner", o);
    request.addParameter("project", p);
    request.addParameter("stack", s);

    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));
    string json = response->getContent();
    if(response)
    {
        switch(response->getResponseCode())
        {
            case 400:
                Log(lWarning) << "The stack: " << s <<" is read only";
            return false;

            case 200:
                Log(lInfo) 	 << "The stack: " << s <<" was deleted on the server.";
            return true;
        }
    }
    return false;
}

StringList RenderStackDataAPI::getChannelsInStack(const string& o, const string& p, const string& stack)
{
    RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addParameter("owner", o);
    request.addParameter("project", p);
    request.addParameter("stack", stack);

    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));

    JSONParser parser(response->getContent());
    Log(lInfo) << "Got " << parser.getNumberOfTokens();

	StringList chs = parser.getStringList("channelNames");

    return chs;
}

}


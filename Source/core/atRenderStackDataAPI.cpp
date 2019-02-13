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

StringList RenderStackDataAPI::getChannelsInStack(const string& o, const string& p, const string& stack)
{
    RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addParameter("owner", o);
    request.addParameter("project", p);
    request.addParameter("stack", stack);
//    request.addQuery("stacks");

    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));

    JSONParser parser(response->getContent());
    Log(lInfo) << "Got " << parser.getNumberOfTokens();
//   	const JSONToken* t = parser.getObjectToken("stats");
	StringList chs = parser.getStringList("channelNames");
//    if(t)
//    {
//        chs = parser.getStringList(t);
//    }


    return chs;

//	//http://localhost/render-ws/v1/owner/ATExplorer/project/M33/stack/STI_FF_Session1?api_key=stacks
//    if(!mServiceParameters)
//    {
//        return StringList();
//    }
//
//    stringstream sUrl;
//    sUrl << mServiceParameters->getBaseURL();
//    sUrl << "/owner/" 	<<	mRenderProject.getProjectOwner();
//    sUrl << "/project/" <<	mRenderProject.getRenderProjectName();
//    sUrl << "/stack/" 	<<	stackName << "?api_key=stacks";
//    Log(lDebug5) << "Fetching channels: "<<sUrl.str();
//
//    try
//    {
//        TStringStream* zstrings = new TStringStream;;
//        mLastRequestURL = sUrl.str();
//        mC->Get(mLastRequestURL.c_str(), zstrings);
//
//        if( mC->ResponseCode != HTTP_RESPONSE_OK)
//        {
//            Log(lError) << "Bad HTTP RESPONSE when getching channel names";
//	        return StringList();
//        }
//
//        string s = stdstring(zstrings->DataString);
//
//        //Parse JSON
//        jsmn_parser parser;
//        jsmn_init(&parser);
//
//        int r = jsmn_parse(&parser, s.c_str(), s.size(), NULL, 0);
//        if(r)
//        {
//            jsmn_init(&parser);
//            jsmntok_t* tokens = new jsmntok_t[r];
//            r = jsmn_parse(&parser, s.c_str(), s.size(), &tokens[0], r);
//            if(r)
//            {
//                //find string token "channelNames"
//                for(int i = 0; i < r; i++)
//                {
//                    jsmntok_t tok = tokens[i];
//                    if(tok.type == JSMN_STRING)
//                    {
//                        string sToken = toString(tok, s);
//                        if(sToken == "channelNames")
//                        {
//                            //Next one is an ARRAY object holding the channels..
//                            //parse it into a string
//                            jsmntok_t chs_tok = tokens[i + 1];
//
//                            string chs = toString(chs_tok, s);
//                            chs = stripCharacters(" []\"", chs);
//                            //Get them all as a string..
//                            StringList channels(chs, ',');
//                            channels.sort();
//                            return channels;
//                        }
//                    }
//                }
//            }
//        }
//
//    	Log(lError) << "Failed fetching channels";
//        return StringList();
//    }
//    catch(...)
//    {
//    	Log(lError) << "Failed fetching channels";
//        return StringList();
//    }
}



}


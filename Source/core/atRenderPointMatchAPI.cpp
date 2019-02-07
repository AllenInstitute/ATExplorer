#pragma hdrstop
#include "atRenderPointMatchAPI.h"
#include "atRenderClient.h"
#include "atPointMatchCollection.h"
#include "atRESTRequest.h"
#include "atRESTResponse.h"
#include "atJSONParser.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

RenderPointMatchAPI::RenderPointMatchAPI(RenderClient& rc)
:
RenderAPI("PointMatchAPI", rc)
{}

RenderPointMatchAPI::~RenderPointMatchAPI()
{}

RESTResponse* RenderPointMatchAPI::execute(RESTRequest& request)
{
    //Create a response object
    string result;
    int responseCode = mRC.executeRequest(request, result);
    Log(lDebug) << "HTTP Response Code: " << responseCode;
    return new RESTResponse(result, responseCode);
}

StringList RenderPointMatchAPI::getPointMatchGroupIDs(const string& o, const string& matchCollection)
{
    RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addParameter("owner", o);
    request.addParameter("matchCollection", matchCollection);
    request.addSegment("groupIds");
    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));
    return (response) ?	response->getAsStringList() : StringList();
}

StringList RenderPointMatchAPI::getPPointMatchGroupIDs(const string& o, const string& matchCollection)
{
	RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addParameter("owner", o);
    request.addParameter("matchCollection", matchCollection);
    request.addSegment("pGroupIds");
    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));
    return (response) ?	response->getAsStringList() : StringList();
}

StringList RenderPointMatchAPI::getQPointMatchGroupIDs(const string& o, const string& matchCollection)
{
	RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addParameter("owner", o);
    request.addParameter("matchCollection", matchCollection);
    request.addSegment("qGroupIds");
    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));
    return (response) ?	response->getAsStringList() : StringList();
}

ListOfObjects<PointMatch> RenderPointMatchAPI::getPQMatches(const string& o, const string& mc, const string& pGroup, const string& qGroup)
{
	RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addParameter("owner", o);
    request.addParameter("matchCollection", mc);
    request.addParameter("group", pGroup);
    request.addParameter("matchesWith", qGroup);

    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));

    string json = response->getContent();
    //Parse the response
	JSONParser parser(json);

    //Use our knowledge of the JSON..
 	vector<double>  w 	= parser.get1DDoubleArray("matches", "w");
 	vector<Point2D> p   = parser.get2DDoubleArray("matches", "p");
 	vector<Point2D> q   = parser.get2DDoubleArray("matches", "q");

    Log(lInfo) << w.size() << ":" <<p.size() << ":" << q.size();
    if((w.size() != p.size() || w.size() != q.size()))
    {
        Log(lError) << "Bad pointmatch data..";
		return ListOfObjects<PointMatch>();
    }

    //Create the list
	ListOfObjects<PointMatch> list;
    for(int point = 0; point < w.size(); point++)
    {
	    PointMatchPoint pmpP(pGroup, PointMatchPoint::pGroup, p[point], w[point]);
	    PointMatchPoint pmpQ(qGroup, PointMatchPoint::qGroup, q[point], w[point], &pmpP);
        pmpP.assignCorrespondingPoint(pmpQ);

        list.append(PointMatch(pmpP, pmpQ));
    }

    return list;
}

bool RenderPointMatchAPI::deletePointMatchCollection(const string& o, const string& mc)
{
	RESTRequest request(mRC.getBaseURL(), rmDelete);
    request.addParameter("owner", o);
    request.addParameter("matchCollection", mc);

    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));
    string json = response->getContent();
    if(response)
    {
        switch(response->getResponseCode())
        {
            case 404:
                Log(lWarning) << "The collection: " << mc <<" was not found";
            return false;
        }
    }
    return false;
}


ListOfPointers<PointMatchCollection*> RenderPointMatchAPI::getPointMatchCollectionsForOwner(const string& o)
{
	RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addParameter("owner", o);
    request.addSegment("matchCollections");
    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));

    StringList list;
	if(response)
    {
    	list = response->getAsStringList();
    }

    //Put contexts in a list
    ListOfPointers<PointMatchCollection*> contexts;
    for(int i = 0; i < list.count(); i++)
    {
        PointMatchCollection* pc = new PointMatchCollection(o, list[i]);
        contexts.append(pc);
    }

//
//    //Parse JSON
//    jsmn_parser parser;
//    jsmn_init(&parser);
//
//    int r = jsmn_parse(&parser, json.c_str(), json.size(), NULL, 0);
//    if(r)
//    {
//        jsmn_init(&parser);
//        jsmntok_t* tokens = new jsmntok_t[r];
//        r = jsmn_parse(&parser, json.c_str(), json.size(), &tokens[0], r);
//        jsmntok_t main_tok = tokens[0];
//        int recordOffset(9);
//        if(main_tok.type == JSMN_ARRAY)
//        {
//            //Parse out records
//            for(int i = 0; i < main_tok.size; i++)
//            {
//                string name 	= toString(      tokens[7 + i*recordOffset], json);
//			    int pairCount 	= toInt(toString(tokens[9 + i*recordOffset], json));
//                PointMatchCollection* pc = new PointMatchCollection(o, name);
//                if(pc)
//                {
//                    contexts.append(pc);
//                }
//            }
//        }
//    }
//
    return contexts;
}

StringList RenderPointMatchAPI::getPointMatchCollectionNamesForOwner(const string& o)
{
//    stringstream sUrl;
//    sUrl << mServiceParameters->getBaseURL();
//    sUrl << "/owner/" << o;
//    sUrl << "/matchCollections";
//    Log(lDebug5) << "Fetching matchCollections for owner: "<<sUrl.str();
//
//    TStringStream* zstrings = new TStringStream;;
//    mC->Get(sUrl.str().c_str(), zstrings);
//
//    if(mC->ResponseCode != HTTP_RESPONSE_OK)
//    {
//        Log(lError) << "Failed fetching collections";
//        return StringList();
//    }
//
//    string json = stdstring(zstrings->DataString);
//    Log(lDebug1) << "Render Response: "<<json;
//
//    //Put collections in this list
//    StringList collections;
//
//    //Parse JSON
//    jsmn_parser parser;
//    jsmn_init(&parser);
//
//    int r = jsmn_parse(&parser, json.c_str(), json.size(), NULL, 0);
//    if(r)
//    {
//        jsmn_init(&parser);
//        jsmntok_t* tokens = new jsmntok_t[r];
//        r = jsmn_parse(&parser, json.c_str(), json.size(), &tokens[0], r);
//        jsmntok_t main_tok = tokens[0];
//        int recordOffset(9);
//        if(main_tok.type == JSMN_ARRAY)
//        {
//            //Parse out records
//            for(int i = 0; i < main_tok.size; i++)
//            {
//                string name 	= toString(      tokens[7 + i*recordOffset], json);
//			    int pairCount 	= toInt(toString(tokens[9 + i*recordOffset], json));
//                PointMatchCollection* pc = new PointMatchCollection(o, name);
//                if(pc)
//                {
//                    collections.append(pc->getName());
//                }
//            }
//        }
//    }
//
//    collections.sort();
//    return collections;
}


}


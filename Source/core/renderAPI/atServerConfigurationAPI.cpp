#pragma hdrstop
#include "atServerConfigurationAPI.h"
#include "atRenderClient.h"
#include "atPointMatchCollection.h"
#include "atRESTRequest.h"
#include "atRESTResponse.h"
#include "atJSONParser.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

ServerConfigurationAPI::ServerConfigurationAPI(RenderClient& rc)
:
RenderAPI("PointMatchAPI", rc)
{}

ServerConfigurationAPI::~ServerConfigurationAPI()
{}

string ServerConfigurationAPI::getServerProperties()
{
	RESTRequest request(mRC.getBaseURL(), rmGet);
    request.addSegment("serverProperties");
    RESTResponse* response = dynamic_cast<RESTResponse*>(execute(request));

    //Just return the json..
    return response->getContent();


//    JSONParser parser(response->getContent());
//    list<const JSONToken*> objects =  parser.getListOfObjects();
//
//    Log(lDebug) << "Found " << objects.size() << " objects";
//
//
//    //Check how many records
//    StringList list;
//    string filePath;
//    string properties;
//    const JSONToken* t = parser.getToken(0);
//
//    parser.g
//    if(t && (t->type == JSMN_OBJECT))
//    {
//        filePath   = parser.getStringValueInObject(t, "filePath");
//        properties = parser.getStringValueInObject(t, "properties");
//    }
//
//    StringList result;
//    result.append(filePath);
//    result.append(properties);
//    return result;
}


}


#pragma hdrstop
#include "atPointMatchCollection.h"
#include "dslStringList.h"
#include "atStringUtils.h"
#include "atExceptions.h"
#include "atRenderClient.h"
#include "atJSONParser.h"

//---------------------------------------------------------------------------
namespace at
{

using namespace dsl;

PointMatchCollection::PointMatchCollection(const string& owner, const string& name, RenderClient*  renderService)
:
RenderObject(renderService),
mOwner(owner),
mName(name)
{}

PointMatchCollection::~PointMatchCollection()
{}

bool PointMatchCollection::fetch()
{
    mGroupIDs = getGroupIDs();
    return true;
}

StringList PointMatchCollection::getGroupIDs()
{
    return requestStringList("groupIds");
}

StringList PointMatchCollection::getPGroupIDs()
{
    return requestStringList("pGroupIds");
}

StringList PointMatchCollection::getQGroupIDs()
{
    return requestStringList("qGroupIds");
}

StringList PointMatchCollection::requestStringList(const string& request)
{
    stringstream sUrl;
    sUrl << mRenderService->getBaseURL();
    sUrl << "/owner/" << mOwner;
    sUrl << "/matchCollection/" << mName;
    sUrl << "/" <<request;

    Log(lDebug5) << "Request url: "<<sUrl.str();
    string json = mRenderService->request(sUrl.str());
    Log(lDebug1) << "Render Response: "<<json;

    //Put collections in this list
    JSONParser p(json);
    return p.getStringList();
}

List<PointMatch> PointMatchCollection::getPQMatches(const string& pGroup, const string& qGroup)
{
	List<PointMatch> list;
    stringstream sUrl;
    sUrl << mRenderService->getBaseURL();
    sUrl << "/owner/" 			<<mOwner;
    sUrl << "/matchCollection/"	<<mName;
    sUrl << "/group/"			<<pGroup;
    sUrl << "/matchesWith/"		<<qGroup;
    Log(lDebug5) << "Request url: "<<sUrl.str();
    string json = mRenderService->request(sUrl.str());
    Log(lDebug1) << "Render Response: "<<json;

    //Parse the response
	JSONParser p(json);
    p.get2DDoubleArray("matches", "p");
    p.get2DDoubleArray("matches", "q");

    return list;
}

bool PointMatchCollection::deleteCollection()
{
    stringstream sUrl;
    sUrl << mRenderService->getBaseURL();
    sUrl << "/owner/" 			<<mOwner;
    sUrl << "/matchCollection/"	<<mName;

    Log(lDebug5) << "Deleting matchCollection URL: "<<sUrl.str();

//    TStringStream* zstrings = new TStringStream;;
//    mC->Delete(sUrl.str().c_str(), zstrings);
//
//    if(mC->ResponseCode != HTTP_RESPONSE_OK)
//    {
//        Log(lError) << "Failed deleting point match collection";
//        return false;
//    }
//
//    string json = stdstring(zstrings->DataString);
//    Log(lDebug1) << "Render Response: "<<json;
    return true;
}

}


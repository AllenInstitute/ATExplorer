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
mName(name),
mMatchesJSONTokenIndex(11) //This is Known
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

    //Use our knowledge of the JSON..
    JSONToken matchesObject = p.getToken(mMatchesJSONTokenIndex);

    //Look for 6 arrays, PXY, PX, PY, QXY, QX, QY and W
	JSONToken pqArrayToken   = p.getToken(mMatchesJSONTokenIndex);
    JSONToken pxToken = p.getArrayToken(mMatchesJSONTokenIndex, 2);
    JSONToken pyToken = p.getArrayToken(mMatchesJSONTokenIndex, 3);
                                                                //#4 is qXY
    JSONToken qxToken = p.getArrayToken(mMatchesJSONTokenIndex, 5);
    JSONToken qyToken = p.getArrayToken(mMatchesJSONTokenIndex, 6);
    JSONToken wToken  = p.getArrayToken(mMatchesJSONTokenIndex, 7);

 	vector<double> px  	   = p.get1DDoubleArray(pxToken.parent + 2, pxToken.size);
 	vector<double> py  	   = p.get1DDoubleArray(pyToken.parent + 2, pxToken.size);
 	vector<double> qx  	   = p.get1DDoubleArray(qxToken.parent + 2, pxToken.size);
 	vector<double> qy  	   = p.get1DDoubleArray(qyToken.parent + 2, pxToken.size);
 	vector<double> weights = p.get1DDoubleArray(wToken.parent  + 2, pxToken.size);

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


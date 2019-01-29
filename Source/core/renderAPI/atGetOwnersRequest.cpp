#pragma hdrstop
#include "atGetOwnersRequest.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

GetOwnersRequest::GetOwnersRequest(const string& baseURL)
:
RenderRequest(baseURL)
{
	mRequestMethod = rmGet;
	mRequestURL << baseURL;
    mRequestURL << "/owners";
}

GetOwnersRequest::~GetOwnersRequest()
{}

////Save data in a StringList
//int GetOwnersRequest::execute()
//{
//    Log(lDebug5) << "Fetching owners: "<<mRequestURL.str();
//
//    try
//    {
//
////        mLastRequestURL = mRequestURL.str();
//
//        if(mRestClient.executeRequest(this) == HTTP_RESPONSE_OK)
//        {
//
//        }
//
//
//    }
//    catch(...)
//    {
//    	Log(lError) << "Failed fetching owners";
//    }
//
//    owners.sort();
//    return owners;
//
//}

}




#pragma hdrstop
#include "atRESTRequest.h"
//---------------------------------------------------------------------------

namespace at
{

RESTRequest::RESTRequest(const string& baseURL)
:
mBaseURL(baseURL),
mRequestMethod(rmUndefined)
{}

RESTRequest::~RESTRequest()
{}

string RESTRequest::getRequestURL()
{
    return mRequestURL.str();
}
}



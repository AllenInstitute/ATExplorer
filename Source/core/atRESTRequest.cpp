#pragma hdrstop
#include "atRESTRequest.h"
//---------------------------------------------------------------------------

namespace at
{

RESTRequest::RESTRequest(const string& baseURL, RequestMethod rm, ExplorerObject* o)
:
mBaseURL(baseURL),
mRequestMethod(rm),
mRequestorObject(o)
{
    mRequestURL << mBaseURL;
}

RESTRequest::~RESTRequest()
{}

void RESTRequest::addParameter(const string& name, const string& value)
{
    mRequestURL << "/" << name << "/" << value;
}

void RESTRequest::addSegment(const string& seg)
{
    mRequestURL << "/" << seg;
}

void RESTRequest::addQuery(const string& q)
{
    mRequestURL << "/?" << "api-key="<<q;
}

string RESTRequest::getRequestURL()
{
    return mRequestURL.str();
}
}



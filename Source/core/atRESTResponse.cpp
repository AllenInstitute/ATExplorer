#pragma hdrstop
#include "atRESTResponse.h"
#include "atJSONParser.h"
//---------------------------------------------------------------------------

namespace at
{

RESTResponse::RESTResponse(const string& response, int code)
:
mResponse(response),
mResponseCode(code)
{}

RESTResponse::~RESTResponse()
{}

StringList RESTResponse::getAsStringList()
{
    JSONParser p(mResponse);
    mStringList = p.getStringList();

    return mStringList;
}

const string& RESTResponse::getContent()
{
    return mResponse;
}

bool RESTResponse::parse()
{
    return false;
}


}

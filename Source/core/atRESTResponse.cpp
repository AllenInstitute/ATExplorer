#pragma hdrstop
#include "atRESTResponse.h"
//---------------------------------------------------------------------------

namespace at
{

RESTResponse::RESTResponse(const string& response)
:
mResponse(response)
{}

RESTResponse::~RESTResponse()
{}

StringList RESTResponse::getStringList()
{
    return mStringList;
}

bool RESTResponse::parse()
{
    return false;
}


}

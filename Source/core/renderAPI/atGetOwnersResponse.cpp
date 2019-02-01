#pragma hdrstop
#include "atGetOwnersResponse.h"
#include "atJSONParser.h"
//---------------------------------------------------------------------------

namespace at
{

GetOwnersRESTResponse::GetOwnersRESTResponse(const string& response)
:
RESTResponse(response, -1)
{
    parse();
}

bool GetOwnersRESTResponse::parse()
{
    JSONParser p(mResponse);
    mStringList = p.getStringList();
    return true;
}


StringList GetOwnersRESTResponse::getOwners()
{
    return mStringList;
}

}
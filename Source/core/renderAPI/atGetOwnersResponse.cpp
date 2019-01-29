#pragma hdrstop
#include "atGetOwnersResponse.h"
#include "atJSONParser.h"
//---------------------------------------------------------------------------

namespace at
{

GetOwnersRESTResponse::GetOwnersRESTResponse(const string& response)
:
RESTResponse(response)
{
    parse();
}

bool GetOwnersRESTResponse::parse()
{
    JSONParser p(mResponse);
    mStringList = p.getStringList();
//    return ;

//     s = stripCharacters("\"[]", s);
//     owners.appendList(StringList(s, ','));
    return true;
}


StringList GetOwnersRESTResponse::getOwners()
{
    return mStringList;
}

}
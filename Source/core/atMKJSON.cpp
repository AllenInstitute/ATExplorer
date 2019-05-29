#pragma hdrstop
#include "atMKJSON.h"
#include <sstream>
#include "dslStringList.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------


using namespace std;
using namespace dsl;
namespace at
{

MKJSON::MKJSON(JSONType type, const string& key)
:
mKey(key),
mJSONType(type),
mIsClosed(false)
{
    if(type == JSON_OBJECT)
    {
        this->createObject(key);
    }
    else
    {
        this->createArray(key);
    }

}

MKJSON::~MKJSON()
{}

void MKJSON::close()
{
    if(mJSONType == JSON_OBJECT)
    {
        mTheJSON = "{" + mTheJSON + "}";
    }
    else
    {
        mTheJSON = "[" + mTheJSON + "]";
    }
    mIsClosed = true;
}

const string& MKJSON::theJSON() const
{
    return mTheJSON;
}

string MKJSON::createObject(const string& key)
{
    if(key.size())
    {
    	mTheJSON  = "\"" + key + "\":{}";
    }
    else
    {
    	mTheJSON  = "{}";
    }

    return mTheJSON;
}

string MKJSON::createArray(const string& key)
{
    if(key.size())
    {
	    mTheJSON  = "\"" + key + "\":[]";
    }
    else
    {
	    mTheJSON = "[]";
    }

    return mTheJSON;
}

bool MKJSON::isEmptyArrayOrObject()
{
    if(mTheJSON.size() < 2)
    {
        Log(lError) << "Bad JSON";
        return true;
    }

    bool empty  = ((mTheJSON[mTheJSON.size() - 2] == '[') || (mTheJSON[mTheJSON.size() -2] == '{') ) ? true : false;
    return empty;
}

ostream& operator<<(ostream& os, const MKJSON& dt)
{
    os << dt.theJSON();
    return os;
}


}


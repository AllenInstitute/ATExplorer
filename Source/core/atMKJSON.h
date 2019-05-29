#ifndef atMKJSONH
#define atMKJSONH
#include "atExplorerObject.h"
#include <string>
#include <sstream>
#include <ostream>
#include "dslLogger.h"
#include "dslLogLevel.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

using std::string;
using std::stringstream;
using dsl::Logger;
using dsl::lError;
using dsl::getHighestLogLevel;
using dsl::StringList;
using std::ostream;

namespace at
{

enum JSONType {JSON_OBJECT, JSON_ARRAY};

class ATE_CORE MKJSON : public ExplorerObject
{
    public:
                                    MKJSON(JSONType type, const string& lbl);
                                    ~MKJSON();

        void                        close();
        const string&          		theJSON() const;

        template<class T>
        string          			append(const string& lbl, const T& value, bool close = false);
        string          			append(const MKJSON& obj);


		friend ostream& 			operator<<(ostream& os, const MKJSON& dt);
        bool                        isEmptyArrayOrObject();

    protected:
        string          			mTheJSON;
        string                  	mKey;

                                    //this just mean that outer braces been "applied" to the object
        bool                        mIsClosed;

	    JSONType                    mJSONType;

        string                      createObject(const string& lbl);
        string                      createArray(const string& lbl);
};

template<class T> inline
string MKJSON::append(const string& lbl, const T& value, bool close)
{
    stringstream s;
    if(mTheJSON.size() < 2)
    {
        Log(lError) << "Bad JSON..";
        return "";
    }

	bool emptyArrayOrObject(isEmptyArrayOrObject());
    mTheJSON.erase(mTheJSON.end() - 1);

    s << string(mTheJSON);
    if(emptyArrayOrObject == false)
    {
        s << ",";
    }

    if(close)
    {
    	s << "{" ;
    }

    s << "\"" << lbl  << "\":" << value;

    if(close)
    {
    	s << "}";
    }

    s << (mJSONType == JSON_ARRAY ? "]" : "}");
    mTheJSON = s.str();
    return mTheJSON;
}

template<> inline
string MKJSON::append<string>(const string& lbl, const string& value, bool close)
{
    stringstream s;
    if(mTheJSON.size() < 2)
    {
        Log(lError) << "Bad JSON..";
        return "";
    }

	bool emptyArrayOrObject(isEmptyArrayOrObject());
    mTheJSON.erase(mTheJSON.end() - 1);

    s << string(mTheJSON);
    if(emptyArrayOrObject == false)
    {
        s << ",";
    }

    if(close)
    {
    	s << "{" ;
    }

    if(lbl.size())
    {
    	s << "\"" << lbl  << "\":";
    }

    s <<"\"" << value << "\"";

    if(close)
    {
    	s << "}";
    }

    s << (mJSONType == JSON_ARRAY ? "]" : "}");
    mTheJSON = s.str();
    return mTheJSON;
}

template<> inline
string MKJSON::append<StringList>(const string& lbl, const StringList& value, bool close)
{
    stringstream s;
	if(mTheJSON.size() < 2)
    {
        Log(lError) << "Bad JSON..";
        return "";
    }
	bool emptyArrayOrObject(isEmptyArrayOrObject());
    mTheJSON.erase(mTheJSON.end() - 1);

    s << string(mTheJSON);
    if(emptyArrayOrObject == false)
    {
        s << ",";
    }

    s << "\"" << lbl  << "\":" << "[";
    for(int i = 0; i < value.count(); i++)
    {
        if(close == true)
        {
          s << "{" << value[i] << "}";
        }
        else
        {
          s << "\"" << value[i] << "\"";
        }

        if(i < value.count() -1)
        {
            s << ",";
        }
    }

   	s << "]";

    s << (mJSONType == JSON_ARRAY ? "]" : "}");
    mTheJSON = s.str();
    return mTheJSON;
}

}

#endif

#pragma hdrstop
#include "atJSONParser.h"
#include "dslStringUtils.h"
#include "atStringUtils.h"
#include <memory>
#include "dslLogger.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;
using namespace std;

JSONParser::JSONParser(const string& json)
:
mTheJSON(json),
mTokens(unique_ptr<jsmntok_t[]>())
{
	jsmn_init(&mParser);
    mNumberOfTokens = jsmn_parse(&mParser, mTheJSON.c_str(), mTheJSON.size(), NULL, 0);
    if(mNumberOfTokens)
    {
        jsmn_init(&mParser);
        mTokens = unique_ptr<jsmntok_t[]>(new jsmntok_t[mNumberOfTokens]);

        int r = jsmn_parse(&mParser, mTheJSON.c_str(), mTheJSON.size(), &mTokens[0], mNumberOfTokens);
        mFirstToken = mTokens[0];
    }
}

JSONParser::~JSONParser()
{}

JSONToken JSONParser::getArrayToken(int afterToken, int nth)
{
    int count(0);
    for(int tokenIndex(afterToken+1); tokenIndex < mNumberOfTokens; tokenIndex++)
    {
        if(mTokens[tokenIndex].type == JSMN_ARRAY)
        {
            count++;
            if(count == nth)
            {
                return mTokens[tokenIndex];
            }
        }
    }

    return JSONToken();
}


StringList JSONParser::getStringList()
{
	StringList list;
    int r = jsmn_parse(&mParser, mTheJSON.c_str(), mTheJSON.size(), NULL, 0);
    if(r)
    {
        jsmn_init(&mParser);
        unique_ptr<jsmntok_t[]> tokens (new jsmntok_t[r]);

        r = jsmn_parse(&mParser, mTheJSON.c_str(), mTheJSON.size(), &tokens[0], r);

        jsmntok_t main_tok = tokens[0];
        if(main_tok.type == JSMN_ARRAY)
        {
            //Parse out records
            for(int i = 0; i < r; i++)
            {
                if(tokens[i].type == JSMN_STRING)
                {
                    string item 	= toString(tokens[i], mTheJSON);
                    list.append(item);
                }
            }
        }
    }
    return list;
}

StringList JSONParser::getStringList(const jsmntok_t& token)
{
	StringList list;
    if(token.type == JSMN_ARRAY)
    {
        //Parse out records
//        string item = toString(token, mTheJSON);
//        item = stripCharacters("[]", item);
//        list = StringList(item, ',');

        for(int i = token.start; i < token.end; i++)
        {
            jsmntok_t aToken = mTokens[i];
            if(aToken.type == JSMN_STRING)
            {
                string item = toString(token, mTheJSON);
                list.append(item);
            }
        }
    }
    return list;
}

string JSONParser::getString(const string& _name)
{
    if(!mNumberOfTokens)
    {
        Log(lError) << "Empty JSON. Could not find value for: "<<_name;
        return "";
    }
    if(mFirstToken.type != JSMN_ARRAY)
    {
        Log(lError) << "Illegal JSON. Could not find value for: "<<_name;
        return "";
    }

    //Find the name
    for(int i = 1; i < mNumberOfTokens; i++)
    {
        jsmntok_t token = mTokens[i];
        if(token.type == JSMN_STRING)
        {
            string name = toString(token, mTheJSON);
            if(name == _name)
            {
                //Next json object is the value
                jsmntok_t value_token = mTokens[i + 1];
                string val = toString(value_token, mTheJSON);
                return val;
            }
        }
    }

    Log(lError) << "JSON Error. Could not find value for: "<<_name;
    return "";
}

vector<double> JSONParser::get1DDoubleArray(int startToken, int size)
{
	vector<double> value;
    int count(0);
    for(int i = startToken; i < startToken + size; i++)
    {
        string v = toString(mTokens[i], mTheJSON);
        double d = toDouble(v);
        value.push_back(d);
    }

    if(value.size() != size)
    {
        Log(lError) << "Parse error in function: " << __FUNC__;
    }
    return value;
}

vector<Point2D> JSONParser::get2DDoubleArray(const string& section, const string& _name)
{
	vector<Point2D> value;
    if(!mNumberOfTokens)
    {
        Log(lError) << "Empty JSON. Could not find value for: "<<_name;
        return value;
    }
    if(mFirstToken.type != JSMN_ARRAY)
    {
        Log(lError) << "Illegal JSON. Could not find value for: "<<_name;
        return value;
    }

    //Find the name
    for(int i = 1; i < mNumberOfTokens; i++)
    {
        jsmntok_t token = mTokens[i];
        if(token.type == JSMN_STRING)
        {
            string name = toString(token, mTheJSON);

            if(name == section) //We found the matches object
            {
                //Find the value for _name
                for(int subIndex = i + 1; subIndex < mNumberOfTokens; subIndex++)
                {
	                jsmntok_t value_token = mTokens[subIndex];
                    if(value_token.type == JSMN_STRING)
                    {
                        string val = toString(value_token, mTheJSON);
                        if(val == _name)
                        {
                            //This token holds the 2D array
                            value_token = mTokens[subIndex + 2];
                        }
                    }
                }

                return value;
            }
        }
    }

    Log(lError) << "JSON Error. Could not find value for: "<<_name;
    return value;
}

JSONToken JSONParser::getToken(int i)
{
    return mTokens[i];
}

}


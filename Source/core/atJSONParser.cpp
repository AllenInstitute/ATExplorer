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
    int r = jsmn_parse(&mParser, mTheJSON.c_str(), mTheJSON.size(), NULL, 0);
    if(r)
    {
        jsmn_init(&mParser);
        mTokens = unique_ptr<jsmntok_t[]>(new jsmntok_t[r]);

        r = jsmn_parse(&mParser, mTheJSON.c_str(), mTheJSON.size(), &mTokens[0], r);
        mFirstToken = mTokens[0];
    }
}

JSONParser::~JSONParser()
{}

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

StringList JSONParser::get2DDoubleArray(const string& header, const string& index)
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
            //Get the "header" object
            for(int i = 0; i < r; i++)
            {
                jsmntok_t token = tokens[i];

                if(token.type == JSMN_STRING)
                {
                    string hdr = toString(token, mTheJSON);
                    if(hdr == header)
	                {
                        //Next item is the matches object
                        jsmntok_t token = tokens[i+4];

                        StringList ps(getStringList(token));

//                        StringList pX(stripCharacters("[]", ps[0]), ',');
//						StringList pY(stripCharacters("[]", ps[0]), ',');


                        Log(lDebug) << ps;
                    }

                }
            }
        }
    }
    return list;
}

}


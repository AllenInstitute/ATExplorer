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
mTokens(unique_ptr<jsmntok_t[]>()),
mTheJSON(json)
{
	jsmn_init(&mParser);
    mNumberOfTokens = jsmn_parse(&mParser, mTheJSON.c_str(), mTheJSON.size(), NULL, 0);
    if(mNumberOfTokens)
    {
        jsmn_init(&mParser);
        mTokens = unique_ptr<jsmntok_t[]>(new jsmntok_t[mNumberOfTokens]);

        int r = jsmn_parse(&mParser, mTheJSON.c_str(), mTheJSON.size(), &mTokens[0], mNumberOfTokens);
        mFirstToken = (mTokens[0]);
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
                if(tokens[i].type == JSMN_STRING || tokens[i].type == JSMN_PRIMITIVE)
                {
                    string item  = toString(&(tokens[i]));
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
        int tokenIndex = getTokenIndex(&token);
        for(int i = tokenIndex; i < (tokenIndex + token.size + 1); i++)
        {
            jsmntok_t aToken = mTokens[i];
            if(aToken.type == JSMN_STRING)
            {
                string item = toString(&aToken);
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
        jsmntok_t& token = mTokens[i];
        if(token.type == JSMN_STRING)
        {
            string name = toString(&token);
            if(name == _name)
            {
                //Next json object is the value
                jsmntok_t& value_token = mTokens[i + 1];
                string val = toString(&value_token);
                return val;
            }
        }
    }

    Log(lError) << "JSON Error. Could not find value for: "<<_name;
    return "";
}

StringList JSONParser::getStringList(const string& _name)
{
    //Find the name
    for(int i = 1; i < mNumberOfTokens; i++)
    {
        jsmntok_t& token = mTokens[i];
        if(token.type == JSMN_STRING)
        {
            string name = toString(&token);
            if(name == _name)
            {
                //Next json object is the stringarray

                jsmntok_t& value_token = mTokens[i + 1];
                return getStringList(value_token);
            }
        }
    }

    Log(lError) << "JSON Error. Could not find value for: "<<_name;
    return StringList();
}

int JSONParser::getTokenIndex(const JSONToken* t)
{
    for(int i = 0; i < mNumberOfTokens; i++)
    {
        if((getToken(i)) == t)
        {
            return i;
        }
    }
    return -1;
}

string JSONParser::getStringValueInObject(const JSONToken* t, const string& _name)
{
    if(!mNumberOfTokens)
    {
        Log(lError) << "Empty JSON. Could not find value for: "<<_name;
        return "";
    }

//    if(mFirstToken.type != JSMN_ARRAY)
//    {
//        Log(lError) << "Illegal JSON. Could not find value for: "<<_name;
//        return "";
//    }

    //Find startToken index
    int startTokenIndex = getTokenIndex(t) + 1;

    //Find the name
    for(int i = startTokenIndex; i < mNumberOfTokens; i++)
    {
        jsmntok_t& token = mTokens[i];
        if(token.type == JSMN_STRING)
        {
            string name = toString(&token);
            if(name == _name)
            {
                //Next json object is the value
                jsmntok_t& value_token = mTokens[i + 1];
                string val = toString(&value_token);
                return val;
            }
        }
    }

    Log(lError) << "JSON Error. Could not find value for: "<<_name;
    return "";
}

StringList JSONParser::getStringList(const JSONToken* t)
{
    //Find startToken index
    int startTokenIndex = getTokenIndex(t) + 1;

    //Find the name
    for(int i = startTokenIndex; i < mNumberOfTokens; i++)
    {
        jsmntok_t& token = mTokens[i];
        if(token.type == JSMN_STRING)
        {
//            string name = toString(&token);
//            if(name == _name)
            {
                //Next json object is the value
                jsmntok_t& value_token = mTokens[i + 1];
                string val = toString(&value_token);
                return val;
            }
        }
    }

    return StringList();
}
vector<double> JSONParser::get1DDoubleArray(const string& objectName, const string& name)
{
	const JSONToken* object_token(NULL);
    if(objectName.size())
    {
	    object_token = const_cast<JSONToken*>(getObjectToken(objectName));
    }
    else
    {
        //Find a way to parse unnamed array..
    }

    if(!object_token)
    {
        return vector<double>();
    }

    const JSONToken* arrayToken  = getArrayToken(object_token, name);
    if(!arrayToken)
	{
        Log(lWarning) << "1D Array: "<<name<<" was not found!";
        return vector<double>();
    }

    int startTokenIndex = getTokenIndex(arrayToken) + 1;
    int size = arrayToken->size;
	vector<double> value;
    for(int i = startTokenIndex; i < startTokenIndex + size; i++)
    {
        string v = toString(mTokens[i]);
        double d = toDouble(v);
        value.push_back(d);
    }

    return value;
}

vector<Point2D> JSONParser::get2DDoubleArray(const string& objectName, const string& name)
{
	const JSONToken* object_token(NULL);
    if(objectName.size())
    {
	    object_token = const_cast<JSONToken*>(getObjectToken(objectName));
    }

    if(!object_token)
    {
        return vector<Point2D>();
    }

    PairOfTokens arrTokens = get2DArrayTokens(object_token, name);

    const JSONToken* xt = arrTokens.first;
    const JSONToken* yt = arrTokens.second;

    if(!xt || !yt)
	{
        Log(lWarning) << "2D Array: "<<name<<" was not found or have the wrong dimensions!";
        return vector<Point2D>();
    }
	vector<Point2D> value;
    int xStart = getTokenIndex(xt) + 1;
    int yStart = getTokenIndex(yt) + 1;
    int size = xt->size;
    int yOffset = yStart - xStart;
    for(int point = xStart; point < xStart + size; point++)
    {
        double x = toDouble(toString(mTokens[point]));
        double y = toDouble(toString(mTokens[point + (yOffset)]));

        value.push_back(Point2D(x,y));
    }

    return value;
}

const JSONToken* JSONParser::getArrayToken(const JSONToken* object_token, const string& name)
{
    int startSearchIndex = getTokenIndex(object_token);
    for(int i = startSearchIndex + 1; i < mNumberOfTokens; i++)
    {
        const JSONToken* t = getToken(i);
        if(t->type == JSMN_ARRAY && (toString(getToken(i-1)) == name))
        {
            return t;
        }
    }
    return NULL;
}

const JSONToken* JSONParser::getNextArrayToken(const JSONToken* token)
{
    int startSearchIndex = getTokenIndex(token) + 1;
    for(int i = startSearchIndex; i < mNumberOfTokens; i++)
    {
        const JSONToken* t = getToken(i);
        if(t->type == JSMN_ARRAY)
        {
            return t;
        }
    }
    return NULL;
}

pair<const JSONToken*, const JSONToken*> JSONParser::get2DArrayTokens(const JSONToken* object_token, const string& arrayName)
{
    const JSONToken* t2 = getArrayToken(object_token, arrayName);

    if(!t2 || (t2->size != 2))
    {
        Log(lError) << "Array: " << arrayName <<" don't exists or has wrong dimensions";
    }

	const JSONToken* arr1 = getNextArrayToken(t2);
    const JSONToken* arr2 = getNextArrayToken(arr1);

    if(!arr1 || !arr2 || (arr1->size != arr2->size))
    {
        Log(lError) << "Array: " << arrayName << " could not be found, or has inconsistent size";
	    const JSONToken* nullToken(NULL);
        return make_pair(nullToken, nullToken);
    }
    return make_pair(arr1, arr2);
}

const JSONToken* JSONParser::getToken(int i)
{
    if(i > (mNumberOfTokens - 1) || i < 0)
    {
        return NULL;
    }
    return &(mTokens[i]);
}

string JSONParser::toString(const JSONToken* t)
{
    if(!t)
    {
        return "";
    }

    return (t) ? at::toString(*t, mTheJSON) : string("");
}

string JSONParser::toString(const JSONToken& t)
{
    return toString(&t);
}

const JSONToken* JSONParser::getObjectToken(const string& name)
{
    for(int i = 1; i < mNumberOfTokens; i++)
    {
        const JSONToken* t = getToken(i);
	    const JSONToken* prevToken(getToken(i - 1));

        if(t && (t->type == JSMN_OBJECT) && (toString(prevToken) == name))
        {
            return t;
        }
    }
    return NULL;
}

const JSONToken* JSONParser::getNamedObjectInObject(const string& name, const JSONToken* t)
{
    //Find startToken index
    int startTokenIndex = getTokenIndex(t);

    //Find the name
    for(int i = startTokenIndex; i < mNumberOfTokens; i++)
    {
        const JSONToken& token = mTokens[i];
        if(token.type == JSMN_OBJECT)
        {
            //Check next token for name
            string aName = toString(mTokens[i + 1]);
            if(aName == name)
            {
                return &token;
            }
        }
    }
    return NULL;
}

const list<const JSONToken*> JSONParser::getListOfObjects()
{
    list<const JSONToken*> tokens;
	int endObject(0);

    for(int i = 1; i < mNumberOfTokens; i++)
    {
        const JSONToken* t = getToken(i);

        if(t && (t->type == JSMN_OBJECT))
        {
            if(t->end > endObject)
            {
            	tokens.push_back(t);
                endObject =t->end;
            }
        }
    }

    return tokens;
}

const list<const JSONToken*> JSONParser::getListOfNamedObjects(const string& name)
{
    list<const JSONToken*> tokens;
    for(int i = 1; i < mNumberOfTokens; i++)
    {
        const JSONToken* t = getToken(i);

        if(t && (t->type == JSMN_OBJECT))
        {
			//Check previous token. Must be string and be equal to name
            const JSONToken* test = getToken(i-1);
            if(test != NULL && test->type == JSMN_STRING && toString(test) == name)
            {
	            tokens.push_back(t);
            }
        }
    }

    return tokens;
}

string toString(const jsmntok_t& key, const string& json)
{
    unsigned int length = key.end - key.start;
    if((key.start + length) <= json.size())
    {
    	return json.substr(key.start, length);
    }
    else
    {
        Log(lError) << "Bad JSON token!";
        return "";
    }
}


}


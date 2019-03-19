#ifndef atJSONParserH
#define atJSONParserH
#include "atExplorerObject.h"
#include "atJSMN.h"
#include "dslStringList.h"
#include "atPoint2D.h"
#include <vector>

#include <list>
//---------------------------------------------------------------------------

namespace at
{

using dsl::StringList;
using dsl::gEmptyString;
using std::unique_ptr;
using std::vector;
using std::list;

//!A JSON token contain start and stop indexes for an object in a json string
typedef jsmntok_t JSONToken;
typedef std::pair<const JSONToken*, const JSONToken*> PairOfTokens;
//!General simple json parser, creating simple, primitive dataobjects from simple queries.

class ATE_CORE JSONParser : public ExplorerObject
{
    public:
                                        JSONParser(const string& json);
                                        ~JSONParser();
        StringList                      getStringList();
        StringList                      getStringList(const JSONToken* t);
        string                          getString(const string& name);
        StringList                      getStringList(const string& name);
        string                          getStringValueInObject(const JSONToken* t, const string& name);

		vector<Point2D>                 get2DDoubleArray(const string& name);
		vector<Point2D>                 get2DDoubleArray(const string& section, const string& name);

		vector<double>                  get1DDoubleArray(const string& objName, const string& arrayName);

        const JSONToken                 getFirstToken(){return mFirstToken;}

        const JSONToken*                getToken(int i);
        const JSONToken*                getObjectToken(const string& name);
        const JSONToken*                getArrayToken(const JSONToken* object_token, const string& name);

		const JSONToken*				getNamedObjectInObject(const string& name, const JSONToken* t);

        int                             getNumberOfTokens(){return mNumberOfTokens;}
        int                             getTokenIndex(const JSONToken* t);

        const list<const JSONToken*>    getListOfObjects();
		const list<const JSONToken*>    getListOfNamedObjects(const string& name);

    protected:
    	jsmn_parser 	                mParser;
        JSONToken                       mFirstToken;
        int                             mNumberOfTokens;
        unique_ptr<JSONToken[]>         mTokens;
        const string&                   mTheJSON;
        StringList                      getStringList(const JSONToken& token);
		string 							toString(const JSONToken& t);
		string 							toString(const JSONToken* t);
        PairOfTokens           			get2DArrayTokens(const JSONToken* object_token, const string& name);
        const JSONToken*                getNextArrayToken(const JSONToken* token);
};

string ATE_CORE toString(const jsmntok_t& key, const string& json);

}


#endif

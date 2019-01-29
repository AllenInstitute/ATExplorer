#ifndef atJSONParserH
#define atJSONParserH
#include "atExplorerObject.h"
#include "atJSMN.h"
#include "dslStringList.h"
#include "atPoint2D.h"
#include <vector>

//---------------------------------------------------------------------------

namespace at
{

using dsl::StringList;
using dsl::gEmptyString;
using std::unique_ptr;
using std::vector;

//!A JSON token contain start and stop indexes for an object in a json string
typedef jsmntok_t JSONToken;

//!General simple json parser, creating simple, primitive dataobjects from simple queries.
class ATE_CORE JSONParser : public ExplorerObject
{
    public:
                                        JSONParser(const string& json);
                                        ~JSONParser();
        StringList                      getStringList();
        string                          getString(const string& name);

		vector<Point2D>                 get2DDoubleArray(const string& name);
		vector<Point2D>                 get2DDoubleArray(const string& section, const string& name);
		vector<double>                  get1DDoubleArray(int startToken, int size);
        const JSONToken                 getFirstToken(){return mFirstToken;}
        JSONToken                       getToken(int i);
        JSONToken                       getArrayToken(int afterToken, int nth);

    protected:
    	jsmn_parser 	                mParser;
        JSONToken                       mFirstToken;
        int                             mNumberOfTokens;
        unique_ptr<JSONToken[]>         mTokens;
        const string&                   mTheJSON;
        StringList                      getStringList(const JSONToken& token);

};

}


#endif

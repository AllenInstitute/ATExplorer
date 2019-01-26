#ifndef atJSONParserH
#define atJSONParserH
#include "atExplorerObject.h"
#include "atJSMN.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::StringList;
using std::unique_ptr;

//!Simple json parsing..
class ATE_CORE JSONParser : public ExplorerObject
{

    public:
                                        JSONParser(const string& json);
                                        ~JSONParser();
        StringList                      getStringList();
		StringList                      get2DDoubleArray(const string& header, const string& index);

    protected:
    	jsmn_parser 	                mParser;
        jsmntok_t                       mFirstToken;
        int                             mNumberOfTokens;
        unique_ptr<jsmntok_t[]>         mTokens;
        const string&                   mTheJSON;
        StringList                      getStringList(const jsmntok_t& token);

};

}


#endif

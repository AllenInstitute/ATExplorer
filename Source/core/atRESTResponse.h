#ifndef atRESTResponseH
#define atRESTResponseH
#include "atExplorerObject.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------
namespace at
{

using dsl::StringList;
class ATE_CORE RESTResponse : public ExplorerObject
{

    public:
                                                RESTResponse(const string& response, int responseCode);
        virtual                                 ~RESTResponse();

		const string&	                        getContent();
        StringList		                        getAsStringList();
        virtual bool                            parse();
        int                                     getResponseCode(){return mResponseCode;}

    protected:
                                                //!Typically JSON format..
		string			                        mResponse;
        int                                     mResponseCode;

                                                //Some data packing
        StringList		                        mStringList;
};


}


#endif

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
                                                RESTResponse(const string& response);
        virtual                                 ~RESTResponse();

		string			                        getContent();
        StringList		                        getStringList();
        virtual bool                            parse();

    protected:
                                                //!Typically JSON format..
		string			                        mResponse;

                                                //Some data packing
        StringList		                        mStringList;
};


}


#endif

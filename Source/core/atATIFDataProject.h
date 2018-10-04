#ifndef atATIFDataProjectH
#define atATIFDataProjectH
#include <string>
#include "atATExplorerProject.h"
#include "dslStringList.h"
#include "atATData.h"
//---------------------------------------------------------------------------

namespace at
{

using std::string;
using std::vector;
using dsl::gEmptyString;
using dsl::StringList;

class ATE_CORE ATIFDataProject : public ATExplorerProject
{
	public:                                 //!Simplify ctors, too many
        	    	                        ATIFDataProject(const string& pName, const string& dataRootFolder);
                                            ATIFDataProject(const ATIFDataProject& rp);
		virtual    	                        ~ATIFDataProject();
        ATIFDataProject&                    operator = (const ATIFDataProject& rhs);

		void 								setDataRootFolder(const string& rFolder);
		string 								getDataRootFolder() const;

        								    //!ProjectManagement
		virtual bool 	   	                write();
        virtual dsl::XMLElement*            addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLElement* docRoot);
		virtual bool 					    loadFromXML(dsl::XMLNode* node);

                                            //Leave this public for convenience..
        ATData*        		                mATData;

	protected:
    	string 		                        mDataRootFolder;

};

}
#endif

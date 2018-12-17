#ifndef atATIFDataProjectH
#define atATIFDataProjectH
#include <string>
#include "atATExplorerProject.h"
#include "dslStringList.h"
#include "atATIFData.h"
//---------------------------------------------------------------------------

namespace at
{

using std::string;
using std::vector;
using dsl::gEmptyString;
using dsl::StringList;

typedef shared_ptr<ATData> ATDataSP;
class ATE_CORE ATIFDataProject : public ATExplorerProject
{
        	    	                        ATIFDataProject(const string& pName, const string& dataRootFolder);
		virtual    	                        ~ATIFDataProject();

		void 								setDataRootFolder(const string& rFolder);
		string 								getDataRootFolder() const;

        								    //!ProjectManagement (xml)
		virtual bool 	   	                write();
        virtual dsl::XMLElement*            addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLElement* docRoot);
		virtual bool 					    loadFromXML(dsl::XMLNode* node);

                                            //Leave this public for convenience (?), or write handlers..
        ATIFData   			                mATIFData;
};

}
#endif

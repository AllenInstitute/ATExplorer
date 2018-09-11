#ifndef atATDataProjectItemH
#define atATDataProjectItemH
#include <string>
#include <vector>
#include "Poco/Path.h"
#include "atATProjectItem.h"
#include "atExplorerCoreExporter.h"
#include "atATDataUtils.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

using dsl::gEmptyString;
using dsl::shared_ptr;
using Poco::Path;
using std::string;
using std::vector;

namespace at
{

class ATData;
class ATE_CORE ATDataProjectItem : public ATProjectItem
{
    public:
                                        ATDataProjectItem(const string& lbl, const shared_ptr<ATData>& data = shared_ptr<ATData>());
                                        ATDataProjectItem(const string& lbl, const Path& basePath, ATDataFileFormat atDataFormat = atAllen);

                                        //!ProjectManagement
        virtual bool 	   	            write();
        virtual dsl::XMLElement*        addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
        virtual bool 					loadFromXML(dsl::XMLNode* node);


    protected:
		Path		        			mBasePath;
        shared_ptr<ATData>              mATData;

};

}
#endif

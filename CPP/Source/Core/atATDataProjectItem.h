#ifndef atATDataProjectItemH
#define atATDataProjectItemH
#include <string>
#include <vector>
#include "Poco/Path.h"
#include "atATProject.h"
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
class AT_E_CORE ATDataProjectItem : public ATProject
{
    public:
                                        ATDataProjectItem(const shared_ptr<ATData>& data);
                                        ATDataProjectItem(const Path& basePath, ATDataFileFormat atDataFormat = atAllen);

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

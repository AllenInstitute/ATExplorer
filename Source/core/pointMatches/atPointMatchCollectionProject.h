#ifndef atPointMatchCollectionProjectH
#define atPointMatchCollectionProjectH
#include <string>
#include "atATExplorerProject.h"
#include "atRenderServiceParameters.h"
#include "dslStringList.h"
#include "atRegionOfInterest.h"
#include "atPointMatchCollection.h"
//---------------------------------------------------------------------------

namespace at
{

using std::string;
using std::vector;
using dsl::gEmptyString;
using dsl::StringList;

class ATE_CORE PointMatchCollectionProject : public ATExplorerProject
{
	public:
        	    	                            PointMatchCollectionProject(const string& projName, const string& owner = gEmptyString, const string& name = gEmptyString);
                                                PointMatchCollectionProject(const string& projName, const PointMatchCollection& pmc);
		virtual    	                            ~PointMatchCollectionProject();
        virtual string                          getTypeName() const;

//        PointMatchCollectionProject&               operator = (const PointMatchCollectionProject& rhs);



        bool                                    setRenderServiceParameters(RenderServiceParameters* rsp);
        RenderServiceParameters*                getRenderServiceParameters() const;
		string							        getPointMatchCollectionProjectName() const;

        								        //!ProjectManagement
		virtual bool 	   	                    write();
        virtual dsl::XMLElement*                addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLElement* docRoot);
		virtual bool 					        loadFromXML(dsl::XMLNode* node);

                                                //!Made public for convenience
		PointMatchCollection 					mPointMatchCollection;


	protected:
		RenderServiceParameters*                mRenderService;

};

}
#endif

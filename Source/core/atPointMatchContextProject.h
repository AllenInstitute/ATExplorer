#ifndef atPointMatchContextProjectH
#define atPointMatchContextProjectH
#include <string>
#include "atATExplorerProject.h"
#include "atRenderServiceParameters.h"
#include "dslStringList.h"
#include "atRegionOfInterest.h"
#include "atPointMatchContext.h"
//---------------------------------------------------------------------------

namespace at
{

using std::string;
using std::vector;
using dsl::gEmptyString;
using dsl::StringList;

class ATE_CORE PointMatchContextProject : public ATExplorerProject
{
	public:
        	    	                            PointMatchContextProject(const string& projName, const string& owner = gEmptyString, const string& name = gEmptyString, int pairCount = -1);
                                                PointMatchContextProject(const string& projName, const PointMatchContext& pmc);
		virtual    	                            ~PointMatchContextProject();
        virtual string                          getTypeName() const;

//        PointMatchContextProject&               operator = (const PointMatchContextProject& rhs);



        bool                                    setRenderServiceParameters(RenderServiceParameters* rsp);
        RenderServiceParameters*                getRenderServiceParameters() const;
		string							        getPointMatchContextProjectName() const;

        								        //!ProjectManagement
		virtual bool 	   	                    write();
        virtual dsl::XMLElement*                addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLElement* docRoot);
		virtual bool 					        loadFromXML(dsl::XMLNode* node);


	protected:

		PointMatchContext 						mPointMatchContext;
		RenderServiceParameters*                mRenderService;

};

}
#endif

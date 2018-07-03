#ifndef atRenderProjectH
#define atRenderProjectH
#include <string>
#include <vector>
#include "atATProject.h"
#include "atExplorerCoreExporter.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

using std::string;
using std::vector;
using dsl::gEmptyString;
using dsl::StringList;
namespace at
{

class AT_E_CORE RenderProject : public ATProject
{
    public:
                                        RenderProject(const string& name, const string& owner, const string& project, const string& stack);
        void							setupForStack(const string& owner, const string& project, const string& stack);

        string							getProject(){return mProject;}
        string							getProjectOwner(){return mOwner;}
        string							getCurrentStackName(){return mStack;}

                                        //!ProjectManagement
        virtual bool 	   	            write();
        virtual dsl::XMLElement*        addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
        virtual bool 					loadFromXML(dsl::XMLNode* node);


        string 		                    mInfo;
        string 		                    mOwner;

                                        //!This is the "render" project. Not the same as the projects name
        string 		                    mProject;
        string                          mStack;
        StringList					   	mStacks;

    protected:

};

}
#endif

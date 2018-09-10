#ifndef atRenderProjectItemH
#define atRenderProjectItemH
#include <string>
#include <vector>
#include "atATProjectItem.h"
#include "atExplorerCoreExporter.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

using std::string;
using std::vector;
using dsl::gEmptyString;
using dsl::StringList;
namespace ate
{

class ATE_CORE RenderProjectItem : public ATProjectItem
{
    public:
                                        RenderProjectItem(const string& name, const string& owner, const string& project, const string& stack);
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

#ifndef atRenderProjectH
#define atRenderProjectH
#include <string>
#include <vector>
#include "atATExplorerProject.h"
//---------------------------------------------------------------------------

using std::string;
using std::vector;
using dsl::gEmptyString;

class PACKAGE RenderProject : public ATExplorerProject
{
	public:
			    	                    RenderProject(const string& name, const string& owner, const string& project, const string& stack);
			    	                    RenderProject(const string& url);

                                        RenderProject(const RenderProject& rp);
        RenderProject&                  operator=(const RenderProject& rhs);

		void							setupForStack(const string& owner, const string& project, const string& stack);

		string							getProject();
		string							getProjectOwner();
		string							getSelectedStackName();

        								//!ProjectManagement
		virtual bool 	   	            write();
        virtual dsl::XMLElement*        addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
		virtual bool 					loadFromXML(dsl::XMLNode* node);

    	string 		                    mInfo;
    	string 		                    mOwner;

										//!This is the "render" project. Not the same as the projects name
        string 		                    mProject;

        string                          mSelectedStack;
        vector<string>				   	mStacks;

	protected:
};


#endif

#ifndef atRenderProjectH
#define atRenderProjectH
#include <string>
#include <vector>
#include "atVolumeCreatorProject.h"
//---------------------------------------------------------------------------

using std::string;
using std::vector;
using dsl::gEmptyString;

class RenderProject : public VolumeCreatorProject
{
	public:
			    	                    RenderProject(const string& name, const string& owner, const string& project, const string& stack);
		void							setupForStack(const string& owner, const string& project, const string& stack);
//		string							getProjectName(){return mProjectName;}

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
        vector<string>				   	mStacks;

	protected:

};


#endif

#ifndef atRenderProjectH
#define atRenderProjectH
#include <string>
#include <vector>
#include "atATExplorerProject.h"
#include "atRenderServiceParameters.h"
//---------------------------------------------------------------------------

namespace at
{

using std::string;
using std::vector;
using dsl::gEmptyString;

class PACKAGE RenderProject : public ATExplorerProject
{
	public:
        	    	                    RenderProject(const string& url);
        	    	                    RenderProject(const RenderServiceParameters& rs, const string& name, const string& owner, const string& project);
			    	                    RenderProject(const string& name, const string& owner, const string& project, const string& stack);
                                        RenderProject(const RenderProject& rp);
		virtual    	                    ~RenderProject();
        RenderProject&                  operator = (const RenderProject& rhs);

		void							init(const string& owner, const string& project, const string& stack);
        void                            assignLocalCacheRootFolder(const string& rFolder);
        string                          getLocalCacheFolder();

        RenderServiceParameters         getRenderServiceParameters();
		string							getRenderProjectName();
		string							getProjectOwner();
		string							getSelectedStackName();

        								//!ProjectManagement
		virtual bool 	   	            write();
        virtual dsl::XMLElement*        addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
		virtual bool 					loadFromXML(dsl::XMLNode* node);

	protected:
    	string 		                    mInfo;
    	string 		                    mOwner;
//        RenderLocalCache                mCache;
        string                          mLocalCacheRootFolder;

										//!This is the "render" project. Not the same as the projects name
        string 		                    mRenderProjectName;
        string                          mSelectedStack;
        vector<string>				   	mStacks;

                                        //Tissue section
        int   	                     	mSelectedSection;
		RenderServiceParameters         mRenderService;

};


}
#endif

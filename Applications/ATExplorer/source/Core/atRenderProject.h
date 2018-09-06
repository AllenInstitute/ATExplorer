#ifndef atRenderProjectH
#define atRenderProjectH
#include <string>
#include "atATExplorerProject.h"
#include "atRenderServiceParameters.h"
#include "dslStringList.h"
#include "atRegionOfInterest.h"
//---------------------------------------------------------------------------

namespace at
{

using std::string;
using std::vector;
using dsl::gEmptyString;
using dsl::StringList;

class PACKAGE RenderProject : public ATExplorerProject
{
	public:                             //!Simplify ctors
        	    	                    RenderProject(const string& url);
        	    	                    RenderProject(const RenderServiceParameters& rs, const string& name, const string& owner, const string& project);
			    	                    RenderProject(const string& name, const string& owner, const string& project, const string& stack);
                                        RenderProject(const RenderProject& rp);
		virtual    	                    ~RenderProject();


        RenderProject&                  operator = (const RenderProject& rhs);
		void							init(const string& owner, const string& project, const string& stack);
        void                            assignLocalCacheRootFolder(const string& rFolder);
        string                          getLocalCacheFolder() const;
        string                          getSelectedSectionFileName();

		string							getSelectedStackName() const ;
        bool                            setSelectedStackName(const string& stackName);

        bool                            setSelectedSection(int secNr);
        int	                            getSelectedSection();

        RenderServiceParameters         getRenderServiceParameters() const;
		string							getRenderProjectName() const;
		string							getProjectOwner() const;


        								//!ProjectManagement
		virtual bool 	   	            write();
        virtual dsl::XMLElement*        addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
		virtual bool 					loadFromXML(dsl::XMLNode* node);

                                        //For convenience to 'views'
        RegionOfInterest&               getCurrentRegionOfInterestReference();
        int&                            getMinIntensity();
        int&                            getMaxIntensity();

	protected:
    	string 		                    mInfo;
    	string 		                    mOwner;
        string                          mLocalCacheRootFolder;
		//        RenderLocalCache                mCache;

		RegionOfInterest		 		mCurrentROI;

										//!This is the "render" project name. Not the same as the projects name
        string 		                    mRenderProjectName;
        string                          mSelectedStack;
        StringList					   	mStacks;


        int                             mMinIntensity;
        int                             mMaxIntensity;


		RenderServiceParameters         mRenderService;

};

}
#endif

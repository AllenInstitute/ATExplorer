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

class ATE_CORE RenderProject : public ATExplorerProject
{
	public:                                     //!Simplify ctors, too many
        	    	                            RenderProject(const string& url);
			    	                            RenderProject(const string& name, RenderServiceParameters* paras);
			    	                            RenderProject(const string& name, const string& owner, const string& project, const string& stack);
                                                RenderProject(const RenderProject& rp);
		virtual    	                            ~RenderProject();

        virtual string                          getTypeName() const;
        RenderProject&                          operator = (const RenderProject& rhs);

        void                                    assignLocalCacheRootFolder(const string& rFolder);
        string                                  getLocalCacheFolder() const;

		string							        getSelectedStackName() const ;
        bool                                    setSelectedStackName(const string& s);

		string							        getSelectedChannelName() const ;
        bool                                    setSelectedChannelName(const string& s);

        bool                                    setSelectedSection(int secNr);
        int	                                    getSelectedSection();

        bool                                    setRenderServiceParameters(RenderServiceParameters* rsp);
        RenderServiceParameters*                getRenderServiceParameters() const;
		string							        getRenderProjectName() const;
		string							        getProjectOwner() const;

        								        //!ProjectManagement
		virtual bool 	   	                    write();
        virtual dsl::XMLElement*                addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLElement* docRoot);
		virtual bool 					        loadFromXML(dsl::XMLNode* node);

                                                //For convenience to 'views'
        RegionOfInterest&                       getCurrentRegionOfInterestReference();
        int&                                    getMinIntensity();
        int&                                    getMaxIntensity();

//        StringList                              getChannels();

	protected:
    	string 		                            mInfo;
    	string 		                            mOwner;
        string                                  mLocalCacheRootFolder;

        //Add container for roi's
		RegionOfInterest		 		        mCurrentROI;

										        //!This is the "render" project name. Not the same as the projects name
        string 		                            mRenderProjectName;
        string                                  mSelectedStack;
        string                                  mSelectedChannel;
//        StringList                              mChannels;
        StringList					   	        mRenderStacks;

        int                                     mMinIntensity;
        int                                     mMaxIntensity;
		RenderServiceParameters*                mRenderService;

        //Tiffstack(projects) container are children
        //TiffStacks                          mTiffStacks;
};

}
#endif

#ifndef atPointMatchContextProjectH
#define atPointMatchContextProjectH
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

class ATE_CORE PointMatchContextProject : public ATExplorerProject
{
	public:
        	    	                            PointMatchContextProject(const string& url);
			    	                            PointMatchContextProject(const string& name, RenderServiceParameters* paras);
			    	                            PointMatchContextProject(const string& name, const string& owner, const string& project, const string& stack);
                                                PointMatchContextProject(const PointMatchContextProject& rp);
		virtual    	                            ~PointMatchContextProject();

        virtual string                          getTypeName() const;
        PointMatchContextProject&               operator = (const PointMatchContextProject& rhs);
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
		string							        getPointMatchContextProjectName() const;
		string							        getProjectOwner() const;

        								        //!ProjectManagement
		virtual bool 	   	                    write();
        virtual dsl::XMLElement*                addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLElement* docRoot);
		virtual bool 					        loadFromXML(dsl::XMLNode* node);

                                                //For convenience to 'views'
        RegionOfInterest&                       getCurrentRegionOfInterestReference();
        int&                                    getMinIntensity();
        int&                                    getMaxIntensity();

	protected:
    	string 		                            mInfo;
    	string 		                            mOwner;
        string                                  mLocalCacheRootFolder;

        //Add container for roi's
		RegionOfInterest		 		        mCurrentROI;

										        //!This is the "render" project name. Not the same as the projects name
        string 		                            mPointMatchContextProjectName;
        string                                  mSelectedStack;
        string                                  mSelectedChannel;

        StringList					   	        mRenderStacks;

        int                                     mMinIntensity;
        int                                     mMaxIntensity;
		RenderServiceParameters*                mRenderService;

};

}
#endif

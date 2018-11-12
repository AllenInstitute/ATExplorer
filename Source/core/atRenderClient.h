#ifndef atRenderClientH
#define atRenderClientH
#include "dslStringList.h"
#include "dslConstants.h"
#include "atRegionOfInterest.h"
#include "atRenderProject.h"
#include "atFetchImageThread.h"
#include "atRenderLocalCache.h"
#include "atRenderServiceParameters.h"
#include <string>
#include <vector>
#include "atExplorerObject.h"
//---------------------------------------------------------------------------

namespace Idhttp
{
	class TIdHTTP;
}

namespace System
{
	namespace Classes
	{
		class TMemoryStream;
	}
}

namespace at
{

using std::vector;

using dsl::StringList;
using dsl::gEmptyString;
using std::string;
using at::RenderLocalCache;
using System::Classes::TMemoryStream;

typedef void __fastcall (__closure *RCCallBack)(void);

class ATE_CORE RenderClient : public ExplorerObject
{
	public:
							                        RenderClient(RenderProject& rp, Idhttp::TIdHTTP* c, const RenderServiceParameters& p = RenderServiceParameters("", "",80,"/render-ws/v1"), const string& cacheFolder 	= gEmptyString);
							                        ~RenderClient();

                                                    //Todo, init with RenderLayer object
		bool							            init(
                                                         const string& imageType     	= "jpeg-image",
                                                         int z 					    	= 0,
                                                         double scale 			    	= 0.01,
                                                         int minInt						= 0,
                                                         int maxInt						= 65535
                                                         );

		RenderServiceParameters                     getRenderServiceParameters();
		void							            setBaseURL(const string& baseURL);
		StringList						            getServerProperties();
		StringList						            getOwners();
        StringList						            getProjectsForOwner(const string& o);
        StringList						            getStacksForProject(const string& owner, const string& p);
        RenderProject                               getCurrentProject();
        StringList                                  getROIFoldersForCurrentStack();
		TMemoryStream*								getImageMemory();
        bool                                        renameStack(const string& currentStackName, const string& newName);
        void                                        setSelectedStackName(const string& sName);
		void				                        clearImageMemory();
		string				                        getURL();
		const char* 		                        getURLC();
        TMemoryStream*		                        getImage(int z = 0);
        bool				                        getImageInThread(int z , StringList& paras);
        TMemoryStream*		                        reloadImage(int z = 0);
        string							            getURLForZ(int z);
        bool				                        checkCacheForCurrentURL();
        string				                        getImageLocalCachePath();
        string				                        getImageLocalCachePathAndFileName();
		string 										getImageLocalCachePathAndFileNameForZ(int z);
        string							            getProjectName();

        void							            setLocalCacheFolder(const string& f);
        string							            getLocalCacheFolder();

        StringList						            getZs();
        vector<int>						            getValidZs();
		RegionOfInterest 						    getLayerBoundsForZ(int z);
        RegionOfInterest						    getOptimalXYBoxForZs(const vector<int>& zs = vector<int>(0));
	    vector<RegionOfInterest>				    getLayerBounds();
        RenderProject&					            getProject();
        void										assignOnImageCallback(RCCallBack cb);
        void										copyImageData(MemoryStruct chunk);
		Idhttp::TIdHTTP*                            getConnection();
        void                                        assignConnection(Idhttp::TIdHTTP* c);
        string                                      getBaseURL();
        RenderProject                               getRenderProject();
        void                                        setRenderProject(const RenderProject& rp);
		double        								getLowestResolutionInCache(const RegionOfInterest& roi);

        string                                      getCacheRoot();
        string                                      getLastRequestURL();

    private:
    												//!This is the HTTP connection
                                                    //!Could use CURL instead..
		Idhttp::TIdHTTP* 	                        mC;

        string                                      mLastRequestURL;
        											//!Memory to hold image data retrieved from server
		TMemoryStream* 		                        mImageMemory;

        											//!List of bounds
        vector<RegionOfInterest>				    mLayerBounds;

    	int				                            mZ;
        double				                        mScale;

        RenderServiceParameters                     mRenderService;

        RenderProject&					            mRenderProject;
        RenderLocalCache                            mCache;
        string 			                            mImageType;

        int								            mMinIntensity;
        int								            mMaxIntensity;
        RegionOfInterest						    parseBoundsResponse(const string& s);
        FetchImageThread							mFetchImageThread;
};

}
#endif

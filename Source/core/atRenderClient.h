#ifndef atRenderClientH
#define atRenderClientH
#include "dslStringList.h"
#include "dslConstants.h"
#include "atRegionOfInterest.h"
#include "atRenderProject.h"
#include "atFetchImageThread.h"
#include "atRenderLocalCache.h"
#include "atRenderServiceParameters.h"
#include "atRESTClient.h"
#include "atGenericList.h"
#include <string>
#include <vector>
//---------------------------------------------------------------------------


//Use CURL instead of Indy..
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

class PointMatchCollection;
using std::vector;
using dsl::StringList;
using dsl::gEmptyString;
using std::string;

using System::Classes::TMemoryStream;

typedef void __fastcall (__closure *RCCallBack)(void);


//Create "RenderObjects" and give them a pointer
//Derive from a RestClient class

class ATE_CORE RenderClient : public RESTClient
{
	public:
							                        RenderClient(shared_ptr<Idhttp::TIdHTTP> c, const string& host, const string& name = "");
//							                        RenderClient(RenderProject& rp, Idhttp::TIdHTTP* c, const RenderServiceParameters* p = (NULL), const string& cacheFolder 	= gEmptyString);
							                        ~RenderClient();

                                                    //Todo, init with RenderLayer object
		bool							            init(
                                                         const string& imageType     	= "jpeg-image",
                                                         int z 					    	= 0,
                                                         double scale 			    	= 0.01,
                                                         int minInt						= 0,
                                                         int maxInt						= 65535
                                                         );

		RESTResponse* 								execute(RESTRequest& request);
		void                     					setRenderServiceParameters(RenderServiceParameters* rp);
		const RenderServiceParameters*              getRenderServiceParameters();

        string                                      getBaseURL();
		StringList						            getServerProperties();
		StringList						            getOwners();
        StringList						            getProjectsForOwner(const string& o);

                                                    //Pointmatch API's
		StringList									getPointMatchCollectionNamesForOwner(const string& o);
		List<PointMatchCollection*>    	 	  		getPointMatchCollectionsForOwner(const string& o);
//		StringList									getPointMatchGroupIDs(const string& o, const string& matchCollection);
//		StringList									getPPointMatchGroupIDs(const string& o, const string& matchCollection);
//		StringList									getQPointMatchGroupIDs(const string& o, const string& matchCollection);
//        bool                                        deletePointMatchCollection(const string& owner, const string& matchCollection);

        StringList						            getStacksForProject(const string& owner, const string& p);
        StringList                                  getChannelsInStack(const string& stackName);
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
		string 										getImageLocalCachePathAndFileNameForZ(int z, const string& chs);
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

        RenderProject                               getRenderProject();
        void                                        setRenderProject(const RenderProject& rp);
		double        								getLowestResolutionInCache(const RegionOfInterest& roi);

        string                                      getCacheRoot();
        string                                      getLastRequestURL();
        string                                      request(const string& r);

    private:
    												//!This is the HTTP connection
                                                    //!Could use CURL instead..
//		Idhttp::TIdHTTP* 	                        mC;
        void                                        createRESTServiceParameters(const string& host);
        string                                      mLastRequestURL;

		StringList 									getMatchCollectionAPIResponse(const string& owner, const string& matchCollection, const string& request);

        											//!Memory to hold image data retrieved from server
		TMemoryStream* 		                        mImageMemory;

        											//!List of bounds
        vector<RegionOfInterest>				    mLayerBounds;

    	int				                            mZ;
        double				                        mScale;

//        const RenderServiceParameters*              mRenderServiceParameters;

//        RenderProject&					            mRenderProject;
//        RenderLocalCache                            mCache;
        string 			                            mImageType;

        int								            mMinIntensity;
        int								            mMaxIntensity;
        RegionOfInterest						    parseBoundsResponse(const string& s);
        FetchImageThread							mFetchImageThread;
};

}
#endif

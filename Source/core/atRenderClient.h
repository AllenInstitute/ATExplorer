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
#include "atGenericListOfObjects.h"
#include <string>
#include <vector>
#include "atRenderPointMatchAPI.h"
#include "atRenderStackDataAPI.h"
//---------------------------------------------------------------------------


namespace at
{

class PointMatchCollection;
using std::vector;
using dsl::StringList;
using dsl::gEmptyString;
using std::string;

//using System::Classes::TMemoryStream;

#if defined(__BORLANDC__)
    typedef void __fastcall (__closure *RCCallBack)(void);
#else
    typedef void (*RCCallBack)(void);
#endif


//Derive from a RestClient class
class ATE_CORE RenderClient : public RESTClient
{
	public:
//							                        RenderClient(shared_ptr<Idhttp::TIdHTTP> c = shared_ptr<Idhttp::TIdHTTP>(), const string& host="localhost", const string& name = "");

							                        ~RenderClient();

                                                    //Todo, init with RenderLayer object
		bool							            init(
                                                         const string& imageType     	= "jpeg-image",
                                                         int z 					    	= 0,
                                                         double scale 			    	= 0.01,
                                                         int minInt						= 0,
                                                         int maxInt						= 65535
                                                         );

		void                     					setRenderServiceParameters(RenderServiceParameters* rp);
		const RenderServiceParameters*              getRenderServiceParameters();

        string                                      getBaseURL();
		StringList						            getServerProperties();

                                                    //StackData API
        RenderStackDataAPI                          StackDataAPI;

                                                    //Access renders pointmatch API
        RenderPointMatchAPI                         PointMatchAPI;

//        StringList						            getStacksForProject(const string& owner, const string& p);
//        StringList                                  getChannelsInStack(const string& stackName);
//        RenderProject                               getCurrentProject();
//        StringList                                  getROIFoldersForCurrentStack();
//		TMemoryStream*								getImageMemory();
//        bool                                        renameStack(const string& currentStackName, const string& newName);

		void				                        clearImageMemory();
		string				                        getURL();
		const char* 		                        getURLC();
//        TMemoryStream*		                        getImage(int z = 0);
        bool				                        getImageInThread(int z , StringList& paras,const string& channel, const RenderLocalCache& cache, const RenderProject& rp);
//        TMemoryStream*		                        reloadImage(int z = 0);
        string							            getURLForZ(int z, const RenderProject& rp);
//        bool				                        checkCacheForCurrentURL();
//        string							            getProjectName();

//        void							            setLocalCacheFolder(const string& f);
//        string							            getLocalCacheFolder();

//        StringList						            getZs();
//        vector<int>						            getValidZs();
		RegionOfInterest 						    getLayerBoundsForZ(int z, RenderProject& rp);
        RegionOfInterest						    getOptimalXYBoxForZs(const vector<int>& zs = vector<int>(0));
	    vector<RegionOfInterest>				    getLayerBounds();
        RenderProject&					            getProject();
        void										assignOnImageCallback(RCCallBack cb);
        void										copyImageData(MemoryStruct chunk);
//		Idhttp::TIdHTTP*                            getConnection();
//        void                                        assignConnection(Idhttp::TIdHTTP* c);

//        RenderProject                               getRenderProject();
//        void                                        setRenderProject(const RenderProject& rp);
//		double        								getLowestResolutionInCache(const RegionOfInterest& roi);

//        string                                      getCacheRoot();
        string                                      getLastRequestURL();
//        string                                      request(const string& r);
        shared_ptr<FetchImageThread>				mFetchImageThread;
    private:

        void                                        createRESTServiceParameters(const string& host);
        string                                      mLastRequestURL;


		StringList 									getMatchCollectionAPIResponse(const string& owner, const string& matchCollection, const string& request);

        											//!Memory to hold image data retrieved from server
//		TMemoryStream* 		                        mImageMemory;

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
};

}
#endif

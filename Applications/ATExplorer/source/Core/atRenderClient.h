#ifndef atRenderClientH
#define atRenderClientH
#include <string>
#include "dslStringList.h"
#include "dslConstants.h"
#include <vector>
#include "atRegionOfInterest.h"
#include "atRenderProject.h"
#include "atFetchImageThread.h"
#include "atRenderLocalCache.h"
//---------------------------------------------------------------------------

using std::vector;
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

using System::Classes::TMemoryStream;
using dsl::StringList;
using dsl::gEmptyString;
using std::string;
using at::RenderLocalCache;

typedef void __fastcall (__closure *RCCallBack)(void);

class PACKAGE RenderClient
{
	public:
							                        RenderClient(Idhttp::TIdHTTP* c, const string& baseURL = gEmptyString, const string& cacheFolder 	= gEmptyString);
							                        ~RenderClient();

                                                    //Todo, init with RenderLayer object
		bool							            init(				  	const string& owner 	    = gEmptyString,
                        	                        					  	const string& project 	    = gEmptyString,
                                                                          	const string& stack 	    = gEmptyString,
                                                                          	const string& imageType     = "jpeg-image",
                                                                          	int z 					    = 0,
                                                                          	const RegionOfInterest& box 	    = RegionOfInterest(),
                                                                            double scale 			    = 0.01,
                                                                            int	minInt					= 0,
                                                                            int maxInt					= 65535
                                                                            );

		void							            setBaseURL(const string& baseURL);
		StringList						            getOwners();
        StringList						            getProjectsForOwner(const string& o);
        StringList						            getStacksForProject(const string& owner, const string& p);
        RenderProject                               getCurrentProject();
        StringList                                  getROIFoldersForCurrentStack();
		TMemoryStream*								getImageMemory();
        bool                                        renameStack(const string& currentStackName, const string& newName);

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

    private:
    												//!This is the HTTP connection
		Idhttp::TIdHTTP* 	                        mC;

        											//!Memory to hold image data retrieved from server
		TMemoryStream* 		                        mImageMemory;

        											//!List of bounds
        vector<RegionOfInterest>				    mLayerBounds;

    	int				                            mZ;
        double				                        mScale;
        string			                            mBaseURL;
        RenderProject					            mProject;
        RenderLocalCache                            mCache;
        string 			                            mImageType;
        RegionOfInterest			                mRegionOfInterest;
        int								            mMinIntensity;
        int								            mMaxIntensity;
        RegionOfInterest						    parseBoundsResponse(const string& s);
        FetchImageThread							mFetchImageThread;
};

#endif

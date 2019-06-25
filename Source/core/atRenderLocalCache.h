#ifndef atRenderLocalCacheH
#define atRenderLocalCacheH
#include "atRenderProject.h"
#include "atRegionOfInterest.h"
//---------------------------------------------------------------------------

//!The RenderLocalCache class manages the local cache for a renderproject..
namespace at
{

class ATE_CORE RenderLocalCache : public ExplorerObject
{
    public:
                                    	RenderLocalCache(const string& cr);
                                    	~RenderLocalCache();

        double        		            getLowestResolutionInCache(const RenderProject& rp, const RegionOfInterest& roi) const;

        bool                            checkPresence(const RenderProject& rp, int z, const string& imageType);

        string                          getBasePath() const;
        void                            setBasePath(const string& bp);
        string                          getFileNameForZ(int z, const RenderProject& rp) const;

        string                          getImageLocalCachePath(const RenderProject& rp) const;
        string                          getImageLocalCachePathAndFileName(const RenderProject& rp, const string& z = gEmptyString, const string& imageType = "jpeg-image") const;
        string                          getRenderProjectLocalDataRoot(const RenderProject& rp) const;

        string 		                    getImageLocalCachePathFromURL(const string& url, const string& cachefolder) const;
        string 		                    getImageLocalCacheFileNameAndPathFromURL(const string& url, const string& cachefolder, const string& chs) const;
        string 		                    getRenderProjectLocalDataRootFolderFromURL(const string& url, const string& cachefolder) const;


    protected:
        string                      	mCacheRoot;
};

}

#endif

#ifndef atRenderLayerH
#define atRenderLayerH
#include "Poco/URI.h"
#include "atRegionOfInterest.h"
#include "atRenderProject.h"
#include "atRenderLocalCache.h"
//---------------------------------------------------------------------------
namespace at
{

//!A Render layer denote a certain xyz region of imagedata, existing on render and perhaps in a local cache
class ATE_CORE RenderLayer : public ExplorerObject
{

    public:
                                                        RenderLayer(const string& url, const string& localCacheRootFolder = gEmptyString);
                                                        RenderLayer(RenderProject& url, const RegionOfInterest& roi, const string& localCacheRootFolder = gEmptyString);

        string                                          getURL();
        bool                                            existInCache(const string& f);

        int                                             getZ();
        RegionOfInterest                                getRegionOfInterest();

        int                                             getMinIntensity();
        int                                             getMaxIntensity();
        RenderProject                                   getRenderProject();

    protected:
        Poco::URI                                       mURL;
        int                                             mZ;
        double                                          mScale;
        StringList                                      mChannels;
        RegionOfInterest                                mRegionOfInterest;
        int                                             mMinIntensity;
        int                                             mMaxIntensity;
        RenderProject                                   mRenderProject;

        RenderLocalCache                                mCache;
        string                                          mScheme;
        string                                          mAuthority;
        string                                          mHost;
        int		                                        mPort;
        string                                          mPath;
        string                                          mQuery;
        string                                          mFragment;
        string                                          mPathEtc;
        string                                          mImageType;
};

}

#endif

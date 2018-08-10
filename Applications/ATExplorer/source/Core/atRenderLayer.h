#ifndef atRenderLayerH
#define atRenderLayerH
#include "atATObject.h"
#include "Poco/URI.h"
#include "atRenderbox.h"
#include "atRenderProject.h"
//---------------------------------------------------------------------------
namespace at
{

class PACKAGE RenderLayer : public ATObject
{

    public:
                                        RenderLayer(const string& url);

        string                          getURL();
        string                          getImageLocalCachePath(const string& rootFolder);
        string                          getImageLocalCachePathAndFileName(const string& rootFolder);
        bool                            existInCache(const string& rootFolder);

        int                             getZ();
        RenderBox                       getRenderBox();

        int                             getMinIntensity();
        int                             getMaxIntensity();
        RenderProject                   getRenderProject();

    protected:
        Poco::URI                       mURL;
        int                             mZ;
        double                          mScale;

        RenderBox                       mRenderBox;
        int                             mMinIntensity;
        int                             mMaxIntensity;
        RenderProject                   mRenderProject;

        string                          mScheme;
        string                          mAuthority;
        string                          mHost;
        int		                        mPort;
        string                          mPath;
        string                          mQuery;
        string                          mFragment;
        string                          mPathEtc;
};

}

#endif

#ifndef atRenderLocalCacheH
#define atRenderLocalCacheH
#include "atATObject.h"
#include "atRenderProject.h"
#include "atRegionOfInterest.h"
//---------------------------------------------------------------------------

//!The RenderLocalCache class manages the local cache for a renderproject..
namespace at
{

class PACKAGE RenderLocalCache : public ATObject
{

        public:
                            RenderLocalCache(const string& cr, const RenderProject& rp);

                            ~RenderLocalCache();
		double        		getLowestResolutionInCache(const RenderProject& rp, const RegionOfInterest& roi);
        void                setRenderProject(const RenderProject& rp);
        string              getBasePath();
        void                setBasePath(const string& bp);

        protected:
            RenderProject   mRP;
            string          mCacheRoot;
};

}

#endif

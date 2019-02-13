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
                                        RenderLocalCache(const string& cr, RenderProject* rp = NULL);
                                        ~RenderLocalCache();

		double        		            getLowestResolutionInCache(const RenderProject& rp, const RegionOfInterest& roi);
        void                            setRenderProject(const RenderProject& rp);
        string                          getBasePath() const;
        void                            setBasePath(const string& bp);

        protected:
            const RenderProject*              mRP;
            string                      mCacheRoot;
};

}

#endif

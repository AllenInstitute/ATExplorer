#ifndef atFetchImagesThreadH
#define atFetchImagesThreadH
#include "dslThread.h"
#include "dslStringList.h"
#include "atExplorerCoreExporter.h"
#include <boost/function.hpp>
#include "atRenderLocalCache.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::StringList;
using dsl::Thread;
typedef boost::function<void(void*, void*)> FITCallBack;

class ATE_CORE FetchImagesThread : public dsl::Thread
{
	public:
							                FetchImagesThread(const RenderProject& rp, const RenderLocalCache& cache, const StringList& urls = StringList(dsl::gEmptyString));
							                ~FetchImagesThread();
		void				                setup(const StringList& urls);
        void                                assignCallBacks(FITCallBack one, FITCallBack two, FITCallBack three);
        string                              getRenderStackName();
		virtual void                        run();
        void				                assignUrls(const StringList& urls);
        void				                setChannel(const string& ch);
        void				                setImageType(const string& imType);
        void				                addParameter(const string& api);
        void				                addParameters(const StringList& paras);
        string                              listParameters();
		void								worker();
        StringList                          getImageURLs();
        string                              getCacheRootFolder();

	private:
    	StringList							mImageURLs;
		const RenderLocalCache&             mCache;
        const RenderProject&                mRP;
        string								mOutputDataFolder;
        StringList                          mExtraParameters;
        string		                        mChannel;
        string                              mImageType;
        FITCallBack                         onEnter;
        FITCallBack                         onProgress;
        FITCallBack                         onExit;
};

}
#endif

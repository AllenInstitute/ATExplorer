#ifndef atFetchImageThreadH
#define atFetchImageThreadH
#include "dslThread.h"
#include "dslStringList.h"
#include "atRenderClientUtils.h"
#include <boost/function.hpp>
#include "atRenderLocalCache.h"
#include <curl/curl.h>
//---------------------------------------------------------------------------

namespace at
{
using dsl::StringList;
using dsl::Thread;
typedef boost::function<void(void*, void*)> FITCallBack;

class RenderClient;

class ATE_CORE FetchImageThread : public dsl::Thread
{
	public:
							                FetchImageThread(const RenderProject& rp, RenderClient& rc, const RenderLocalCache& cache);
		void				                setup(const string& url, const string& cacheFolder, const string& z);
		virtual void                        run();
        void				                addParameters(const StringList& paras);
        void				                setChannel(const string& ch);
        void				                addParameter(const string& api);
        string                              listParameters();
		bool				                setCacheRoot(const string& cr);
		void				                worker();
        string                              getFullPathAndFileName();
        FITCallBack                         onImage;

	private:
    	string								mImageURL;
        CURL*								curl_handle;

        int                                 mZ;
        string                              mZString;
		const RenderLocalCache&             mCache;
        const RenderProject&                mRP;
        string								mCacheRootFolder;
        StringList                          mExtraParameters;
        string                              mChannel;

        					                //A renderclient is host, manager for this thread. Give it the memory that is retrieved
        RenderClient&		                mRenderClient;
};

}
#endif

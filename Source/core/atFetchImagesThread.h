#ifndef atFetchImagesThreadH
#define atFetchImagesThreadH
#include "dslThread.h"
#include "dslStringList.h"
#include "atExplorerCoreExporter.h"
#include <boost/function.hpp>
//---------------------------------------------------------------------------

namespace at
{

using dsl::StringList;
using dsl::Thread;
typedef boost::function<void(void*, void*)> FITCallBack;
class ATE_CORE FetchImagesThread : public dsl::Thread
{
	public:
							                FetchImagesThread(const StringList& urls = StringList(""), const string& cacheRoot = "p:\\cache");
		void				                setup(const StringList& urls, const string& cacheFolder);
        void                                assignCallBacks(FITCallBack one, FITCallBack two, FITCallBack three);
		virtual void                        run();
        void				                assignUrls(const StringList& urls);
        void				                addParameter(const string& api);
        void				                addParameters(const StringList& paras);
        string                              listParameters();
		bool				                setCacheRoot(const string& cr);
		void								worker();
        StringList                          getImageURLs();
        string                              getCacheRootFolder();

	private:
    	StringList							mImageURLs;
        string								mCacheRootFolder;
        StringList                          mExtraParameters;
        FITCallBack                         onEnter;
        FITCallBack                         onProgress;
        FITCallBack                         onExit;
};

}
#endif

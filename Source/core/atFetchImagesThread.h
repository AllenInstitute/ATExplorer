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
							                FetchImagesThread(const string& renderStackName = dsl::gEmptyString, const StringList& urls = StringList(dsl::gEmptyString), const string& cacheRoot = dsl::gEmptyString);
		void				                setup(const StringList& urls, const string& cacheFolder);
        void                                assignCallBacks(FITCallBack one, FITCallBack two, FITCallBack three);
        string                              getRenderStackName();
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
        string								mOutputDataFolder;
        string								mRenderStackName;
        StringList                          mExtraParameters;
        FITCallBack                         onEnter;
        FITCallBack                         onProgress;
        FITCallBack                         onExit;
};

}
#endif

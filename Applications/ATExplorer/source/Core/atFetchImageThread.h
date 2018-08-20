#ifndef atFetchImageThreadH
#define atFetchImageThreadH
#include "dslThread.h"
#include "dslStringList.h"
#include "atRenderClientUtils.h"
//---------------------------------------------------------------------------


namespace at
{
using dsl::StringList;
using dsl::Thread;

typedef void __fastcall (__closure *RCCallBack)(void);

class RenderClient;

class PACKAGE FetchImageThread : public dsl::Thread
{
	public:
							                FetchImageThread(RenderClient& rc);
		void				                setup(const string& url, const string& cacheFolder);
		virtual void                        run();
        void				                assignUrl(const string& url);
        void				                addParameters(const StringList& paras);
        void				                addParameter(const string& api);
        string                              listParameters();
		bool				                setCacheRoot(const string& cr);
		void				                worker();

          							        //!The on Image callback is called when image data is retrieved from the server
        RCCallBack							onImage;

	private:
    	string								mImageURL;
        string								mCacheRootFolder;
        StringList                          mExtraParameters;

        					                //A renderclient is host, manager for this thread. Give it the memory that is retrieved
        RenderClient&		                mRenderClient;

};

}
#endif

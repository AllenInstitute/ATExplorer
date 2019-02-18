#ifndef atFetchImageThreadH
#define atFetchImageThreadH
#include "dslThread.h"
#include "dslStringList.h"
#include "atRenderClientUtils.h"
#include <boost/function.hpp>
//---------------------------------------------------------------------------

namespace at
{
using dsl::StringList;
using dsl::Thread;
typedef boost::function<void(void*, void*)> FITCallBack;
typedef void __fastcall (__closure *RCCallBack)(void);

class RenderClient;

class ATE_CORE FetchImageThread : public dsl::Thread
{
	public:
							                FetchImageThread(RenderClient& rc);
		void				                setup(const string& url, const string& cacheFolder);
		virtual void                        run();
        void				                addParameters(const StringList& paras);
        void				                setChannel(const string& ch);
        void				                addParameter(const string& api);
        string                              listParameters();
		bool				                setCacheRoot(const string& cr);
		void				                worker();
        string                              getFullPathAndFileName();

          							        //!The on Image callback is called when image data is retrieved from the server
                                            //Make this a non-vcl dependent callback!
        RCCallBack							onImage;

	private:
    	string								mImageURL;
        string								mCacheRootFolder;
        StringList                          mExtraParameters;
        string                              mChannel;

        					                //A renderclient is host, manager for this thread. Give it the memory that is retrieved
        RenderClient&		                mRenderClient;
};

}
#endif

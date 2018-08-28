#ifndef atFetchImagesThreadH
#define atFetchImagesThreadH
//#include <windows.h>
#include "dslThread.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------


namespace at
{
using dsl::StringList;
using dsl::Thread;

class PACKAGE FetchImagesThread : public dsl::Thread
{
	public:
							                FetchImagesThread(const StringList& urls = StringList(""), const string& cacheRoot = "p:\\cache");
		void				                setup(const StringList& urls, const string& cacheFolder);
		virtual void                        run();
        void				                assignUrls(const StringList& urls);
        void				                addParameters(const StringList& paras);
        void				                addParameter(const string& api);
        string                              listParameters();
		bool				                setCacheRoot(const string& cr);
		void								worker();

	private:
    	StringList							mImageURLs;
        string								mCacheRootFolder;
        StringList                          mExtraParameters;

};

}
#endif

#ifndef atFetchImagesThreadH
#define atFetchImagesThreadH
#include "dslThread.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

using dsl::StringList;
using dsl::Thread;

class FetchImagesThread : public dsl::Thread
{
	public:
							FetchImagesThread(const StringList& urls = StringList(""), const string& cacheRoot = "p:\\cache");
		void				setup(const StringList& urls, const string& cacheFolder);
		virtual void        run();
        void				assignUrls(const StringList& urls);
		void				worker();
		bool				setCacheRoot(const string& cr);
	private:
    	StringList			mImageURLs;
        string				mCacheRootFolder;

};

#endif

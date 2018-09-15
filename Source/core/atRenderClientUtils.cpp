#pragma hdrstop
#include "atRenderClientUtils.h"
#include "dslStringUtils.h"
#include <vector>
#include "atRenderLayer.h"
#include <sstream>
//---------------------------------------------------------------------------
using namespace dsl;
using namespace std;
using namespace at;

//---------------------------------------------------------------------------
int getImageZFromURL(const string& url)
{
    vector<string> cachePaths = splitStringAtWord(url, "/z/");
    if(cachePaths.size() == 2)
    {
    	//Extract
		cachePaths = splitString(cachePaths[1], '/');
        if(cachePaths.size() > 2)
        {
        	return dsl::toInt(cachePaths[1]);
        }
    }
    return -1;
}

string getImageLocalCachePathFromURL(const string& url, const string& cacheRootFolder)
{
    RenderLayer rl(url);
	return rl.getImageLocalCachePath(cacheRootFolder);
}

string getRenderProjectLocalDataRootFolderFromURL(const string& url, const string& cacheFolder)
{
    RenderLayer rl(url);
	return rl.getRenderProjectLocalDataRoot(cacheFolder);
}

//---------------------------------------------------------------------------
string getImageLocalCacheFileNameAndPathFromURL(const string& url, const string& cacheRootFolder)
{
    RenderLayer rl(url);
	return rl.getImageLocalCachePathAndFileName(cacheRootFolder);
}

//CURL related callbacks
//---------------------------------------------------------------------------
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}



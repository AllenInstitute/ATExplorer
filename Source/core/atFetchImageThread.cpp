#pragma hdrstop
#include <Classes.hpp>
#include "atFetchImageThread.h"
#include "dslLogger.h"
#include <curl/curl.h>
#include "Poco/File.h"
#include "dslFileUtils.h"
#include "atRenderClient.h"
//---------------------------------------------------------------------------

namespace at
{
using namespace dsl;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

FetchImageThread::FetchImageThread(RenderClient& rc)
:
mRenderClient(rc),
mImageURL(""),
mCacheRootFolder("")
{}

void FetchImageThread::setup(const string& url, const string& cacheFolder)
{
	mExtraParameters.clear();
	mImageURL = url;
    mCacheRootFolder = cacheFolder;
}

void FetchImageThread::addParameter(const string& api)
{
	mExtraParameters.append(api);
}

void FetchImageThread::addParameters(const StringList& paras)
{
    mExtraParameters.appendList(paras);
}

bool FetchImageThread::setCacheRoot(const string& cr)
{
	//Check if path exists, if not try to create it
	mCacheRootFolder = cr;
    if(folderExists(mCacheRootFolder))
    {
    	return true;
    }
    else
    {
    	return createFolder(mCacheRootFolder);
    }
}

void FetchImageThread::assignUrl(const string& url)
{
	mImageURL = url;
}

void FetchImageThread::run()
{
    worker();
}

void FetchImageThread::worker()
{
	mIsRunning = true;
    mIsTimeToDie = false;
    while(!mIsTimeToDie)
    {
		Log(lDebug4) << "Started Image fetching thread..";

        curl_global_init(CURL_GLOBAL_ALL);

        if(mIsTimeToDie)
        {
            break;
        }

        string url = mImageURL;

        //Check cache first. if already in cache, don't fetch
        string outFilePathANDFileName = getImageLocalCacheFileNameAndPathFromURL(url, mCacheRootFolder);

        Poco::File f(outFilePathANDFileName);
        if(fileExists(outFilePathANDFileName) && f.getSize() > 200)
        {
            Log(lDebug3) << "The image "<<outFilePathANDFileName<<" is in local cache";
            mRenderClient.getImageMemory()->LoadFromFile(outFilePathANDFileName.c_str());
            TThread::Synchronize(NULL, onImage);
        }
        else
        {
            Log(lInfo) << "Fetching Section #: "<<getImageZFromURL(url);
            CURL *curl_handle;
            CURLcode res;

            struct MemoryStruct chunk;

            chunk.memory = (char*) malloc(1);  /* will be grown as needed by the realloc above */
            chunk.size = 0;    /* no data at this point */

            curl_global_init(CURL_GLOBAL_ALL);

            /* init the curl session */
            curl_handle = curl_easy_init();

            string theURL(url);
            for(uint i = 0; i < mExtraParameters.count(); i++)
            {
                theURL += mExtraParameters[i];
            }

            Log(lDebug3) << "Fetching using URL: "<<theURL;
//            string theUrl(url + string("&maxTileSpecsToRender=50"));
            /* specify URL to get */
            curl_easy_setopt(curl_handle, CURLOPT_URL, theURL.c_str());

            /* send all data to this function  */
            curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

            /* we pass our 'chunk' struct to the callback function */
            curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

            /* some servers don't like requests that are made without a user-agent
               field, so we provide one */
            curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

            /* get it! */
            res = curl_easy_perform(curl_handle);

            /* check for errors */
            if(res != CURLE_OK)
            {
                Log(lError) << "curl_easy_perform() failed: " <<  curl_easy_strerror(res);
            }
            else
            {
            	/*
               	* chunk.memory points to a memory block that is chunk.size
               	* bytes big and contains the remote file.
               	*/
                //Make sure path exists, if not create it
                if(createFolder(getFilePath(outFilePathANDFileName)))
                {
                    ofstream of( outFilePathANDFileName.c_str(), std::ofstream::binary);
                    of.write(&chunk.memory[0], chunk.size);

                    Log(lDebug) <<  (long)chunk.size << " bytes retrieved\n";
                    of.close();

                    mRenderClient.getImageMemory()->LoadFromFile(outFilePathANDFileName.c_str());
                    //mRenderClient.copyImageData(chunk);

                    /* cleanup curl stuff */
                    curl_easy_cleanup(curl_handle);
                    free(chunk.memory);

                    /* we're done with libcurl, so clean it up */
                    curl_global_cleanup();

                    //Transfer image to UI
                    TThread::Synchronize(NULL, onImage);
                }
                else
                {
                    Log(lError) << "Failed to write filePath: " << outFilePathANDFileName;
                }
            }
        }
        mIsTimeToDie = true;
	}

  	Log(lInfo) << "Finished Image Fetching Thread.";
    mIsRunning = false;
    mIsFinished = true;
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct*)userp;

  mem->memory = (char*) realloc(mem->memory, mem->size + realsize + 1);

  if(mem->memory == NULL)
  {
    /* out of memory! */
    Log(lError) << "Not enough memory (realloc returned NULL)";
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  return realsize;
}


}

#pragma hdrstop
#include <windows.h>
#include <curl/curl.h>
#include "atFetchImagesThread.h"
#include "dslLogger.h"

//#include <curl/easy.h>
#include "Poco/File.h"
#include "dslFileUtils.h"
#include "atRenderClient.h"

//---------------------------------------------------------------------------

namespace at
{
using namespace dsl;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

FetchImagesThread::FetchImagesThread(const RenderProject& rp, const RenderLocalCache& cache, const StringList& urls)
:
mRP(rp),
mImageURLs(urls),
mCache(cache),
onEnter(nullptr),
onProgress(nullptr),
onExit(nullptr),
mImageType("tiff16-image")
{}

FetchImagesThread::~FetchImagesThread()
{
    Log(lDebug) << "Destructing a FetchImagesThread";
}

void FetchImagesThread::assignCallBacks(FITCallBack one, FITCallBack two, FITCallBack three)
{
    onEnter = one;
    onProgress = two;
    onExit = three;
}

void FetchImagesThread::setup(const StringList& urls)
{
	mExtraParameters.clear();
	mImageURLs = urls;
}

string FetchImagesThread::getURL(int idx)
{
    return mImageURLs[idx];
}

void FetchImagesThread::setChannel(const string& ch)
{
	mChannel = ch;
}

void FetchImagesThread::setImageType(const string& imType)
{
    mImageType = imType;
}

string FetchImagesThread::getRenderStackName()
{
    return mRP.getSelectedStackName();
}

StringList FetchImagesThread::getImageURLs()
{
    return mImageURLs;
}

string FetchImagesThread::getCacheRootFolder()
{
    return mCache.getBasePath();
}

void FetchImagesThread::addParameter(const string& api)
{
	mExtraParameters.append(api);
}

void FetchImagesThread::addParameters(const StringList& paras)
{
    mExtraParameters.appendList(paras);
}

void FetchImagesThread::assignUrls(const StringList& urls)
{
	mImageURLs = urls;
}

void FetchImagesThread::run()
{
    worker();
}

void FetchImagesThread::worker()
{
	mIsRunning = true;
    mIsTimeToDie = false;

    if(onEnter)
    {
        onEnter(this, NULL);
    }

    while(!mIsTimeToDie)
    {
		Log(lDebug4) << "Started Image fetching thread..";
        curl_global_init(CURL_GLOBAL_ALL);

        //Rewrite this later to use threadpools and say # of threads
	    for(uint i = 0; i < mImageURLs.count(); i++)
	    {
        	if(mIsTimeToDie)
            {
            	break;
            }

	    	string url = mImageURLs[i];

            //Check cache first. if already in cache, don't fetch
            string z = toString(getImageZFromURL(mImageURLs[i]));
            string outFilePathANDFileName = mCache.getImageLocalCachePathAndFileName(mRP, z, mImageType, mChannel);
           	Poco::File f(outFilePathANDFileName);
            if(f.exists() && f.getSize() > 200)
            {
            	Log(lDebug3) << "File "<<f.path()<<" is already in local cache. Not fetching";
            }
            else
			{
            	Log(lInfo) << "Fetching using URL: " << mImageURLs[i];

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

                theURL += "&channels=" + mChannel;

	            Log(lDebug3) << "Fetching using URL: "<<theURL;
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
                    if(createFolder(getFilePath(f.path())))
                    {
                        ofstream of(f.path().c_str(), std::ofstream::binary);
                        of.write(&chunk.memory[0], chunk.size);

                        Log(lDebug3) <<  (long)chunk.size << " bytes retrieved";
                        of.close();
                    }
                    else
                    {
                        Log(lError) << "Failed to write file: "<<f.path();
                    }
                }

                /* cleanup curl stuff */
                curl_easy_cleanup(curl_handle);
                free(chunk.memory);

                /* we're done with libcurl, so clean it up */
                curl_global_cleanup();

                if(onProgress)
                {
                    onProgress(this,  &i);
                }
            }
        }

        mIsTimeToDie = true;
	}
  	Log(lInfo) << "Finished Images Fetching Thread.";

    if(onExit)
    {
        onExit(this, NULL);
    }

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

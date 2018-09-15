#ifndef atRenderClientUtilsH
#define atRenderClientUtilsH
#include "atExplorerCoreExporter.h"
#include <string>
//---------------------------------------------------------------------------
using std::string;

ATE_CORE string 		getImageLocalCachePathFromURL(const string& url, const string& cachefolder);
ATE_CORE string 		getImageLocalCacheFileNameAndPathFromURL(const string& url, const string& cachefolder);
ATE_CORE string 		getRenderProjectLocalDataRootFolderFromURL(const string& url, const string& cachefolder);
ATE_CORE int 			getImageZFromURL(const string& url);


struct MemoryStruct
{
  char *memory;
  size_t size;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

#endif
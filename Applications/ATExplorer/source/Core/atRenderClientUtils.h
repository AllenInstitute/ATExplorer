#ifndef atRenderClientUtilsH
#define atRenderClientUtilsH
#include <string>
//---------------------------------------------------------------------------
using std::string;

PACKAGE string 			getImageLocalCachePathFromURL(const string& url, const string& cachefolder);
PACKAGE string 			getImageLocalCacheFileNameAndPathFromURL(const string& url, const string& cachefolder);
PACKAGE int 			getImageZFromURL(const string& url);

struct MemoryStruct
{
  char *memory;
  size_t size;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

#endif

#ifndef atRenderClientUtilsH
#define atRenderClientUtilsH
#include "atExplorerCoreExporter.h"
#include <string>
#include "dslStringList.h"
//---------------------------------------------------------------------------
using std::string;
using dsl::StringList;

ATE_CORE string 			  getImageZFromURL(const string& url);


struct MemoryStruct
{
  char *memory;
  size_t size;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

#endif

#ifndef atATDataUtilsH
#define atATDataUtilsH
#include "atATDataExporter.h"
#include "dslSharedPointer.h"
#include <string>
//---------------------------------------------------------------------------

namespace at
{

using std::string;
class Section;
class FileFolder;
enum  ATDataFileFormat {atAllen, atKM, atBase};

#if defined(__BORLANDC_)
typedef std::tr1::shared_ptr<FileFolder>  FileFolderSP;
#elseif defined(__clang__)
typedef std::shared_ptr<FileFolder>  FileFolderSP;
#endif


int 	  ATE_DATA		getSectionID(const string& filePath);
int 	  ATE_DATA		getTileID(const string& filePath);
int 	  ATE_DATA		getNrOfSections(FileFolderSP channelFolder);

}

#endif

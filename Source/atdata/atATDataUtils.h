#ifndef atATDataUtilsH
#define atATDataUtilsH
#include "atATDataExporter.h"
#include "dslStringList.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::StringList;
using dsl::shared_ptr;

class Section;
class FileFolder;
enum  ATDataFileFormat {atAllen, atKM, atBase};

typedef shared_ptr<FileFolder>  FileFolderSP;

int 	  ATE_DATA		getSectionID(const string& filePath);
int 	  ATE_DATA		getTileID(const string& filePath);
int 	  ATE_DATA		getNrOfSections(FileFolderSP channelFolder);

}

#endif

#ifndef atATDataUtilsH
#define atATDataUtilsH
#include "atATDataExporter.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::StringList;

class Section;
class FileFolder;
enum  ATDataFileFormat {atAllen, atKM, atBase};

int 	  ATE_DATA		getSectionID(const string& filePath);
int 	  ATE_DATA		getTileID(const string& filePath);
int 	  ATE_DATA		getNrOfSections(FileFolder* channelFolder);

}

#endif

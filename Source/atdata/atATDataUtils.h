#ifndef atATDataUtilsH
#define atATDataUtilsH
#include "atATDataExporter.h"
#include <set>
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace ate
{

using std::set;
using dsl::StringList;

class Section;
class FileFolder;
enum  ATDataFileFormat {atAllen, atKM, atBase};

int 	  ATE_DATA		getSectionID(const string& filePath);
int 	  ATE_DATA		getTileID(const string& filePath);
int 	  ATE_DATA		getNrOfSections(FileFolder* channelFolder);

}

#endif

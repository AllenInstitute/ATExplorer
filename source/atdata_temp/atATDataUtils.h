#ifndef atATDataUtilsH
#define atATDataUtilsH
#include "atATDataExporter.h"
#include <set>
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace at
{

using std::set;
using dsl::StringList;

class Section;
class FileFolder;
enum  ATDataFileFormat {atAllen, atKM, atBase};

int 	  AT_DATA		getSectionID(const string& filePath);
int 	  AT_DATA		getTileID(const string& filePath);
int 	  AT_DATA		getNrOfSections(FileFolder* channelFolder);

}

#endif

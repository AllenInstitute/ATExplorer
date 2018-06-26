#ifndef atATIFDataUtilsH
#define atATIFDataUtilsH
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

int 	  ATDATA		getSectionID(const string& filePath);
int 	  ATDATA		getTileID(const string& filePath);
int 	  ATDATA		getNrOfSections(FileFolder* channelFolder);

}

#endif

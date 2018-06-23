#ifndef atATIFDataUtilsH
#define atATIFDataUtilsH
#include <set>
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace at
{
using std::set;
using dsl::StringList;

class Section;
class FileFolder;

int 			getNrOfSections(FileFolder* channelFolder);
StringList 		getTileFileNamesForSection(const set<string>& files, Section* sec);

}

#endif

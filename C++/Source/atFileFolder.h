#ifndef atFileFolderH
#define atFileFolderH
#include "Poco/Path.h"
#include <vector>
#include <string>
#include "atFileSystemObject.h"
#include "dslStringList.h"
#include "atFileFolders.h"
#include <utility>
//---------------------------------------------------------------------------

namespace at
{
using std::pair;
using Poco::Path;
using std::vector;
using std::string;
using dsl::StringList;


typedef pair<int, int>      FolderInfo;

//!A File folder is FileSystem object.
class FileFolder : public FileSystemObject
{
    public:
                            		FileFolder(const Path& name, FileFolder* parent = NULL);
                            		~FileFolder();
        FileFolder*                 getFirstSubFolder();
        FileFolder*   				getSubFolder(const Path& p);
        FileFolders         		getSubFolders(const Path& subPath = Path("."));
        StringList          		getSubFoldersAsList();
        bool                        isPresent(FileSystemObject* child);
        void 				        addSubFolder(FileFolder* child);
        void 				        removeChild(FileSystemObject* child);
        string						getLastPartOfPath();
        string                      directoryName(int n);
        FolderInfo                	scan();

    private:
	    FileFolders					 mSubFolders;
};


}


#endif

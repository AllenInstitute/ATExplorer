#ifndef atFileFolderH
#define atFileFolderH
#include "Poco/Path.h"
#include <vector>
#include <string>
#include "atFileSystemObject.h"
#include "dslStringList.h"
#include <utility>
//---------------------------------------------------------------------------

namespace at
{
using std::pair;
using Poco::Path;
using std::vector;
using std::string;
using dsl::StringList;

class FileFolder;
typedef vector< FileFolder* > FileFolders;
typedef pair<int, int>      FolderInfo;


//!A File folder is FileSystem object.
class FileFolder : public FileSystemObject
{
    public:
                            		FileFolder(const Path& name, FileFolder* parent = NULL);
                            		~FileFolder();
        shared_ptr<FileFolder>   	getSubFolder(const Path& p);
        FileFolders         		getSubFolders(const Path& subPath = Path("."));
        StringList          		getSubFoldersAsList();
        bool                        isPresent(FileSystemObject* child);
        void 				        addChild(FileSystemObject* child);
        void 				        removeChild(FileSystemObject* child);
        string						getLastPartOfPath();
        string                      directoryName(int n);
        FolderInfo                	scan();

    private:
	    vector< FileSystemObject* > mFileFolderContent;
};


}


#endif

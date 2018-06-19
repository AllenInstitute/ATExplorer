#ifndef atFileFolderH
#define atFileFolderH
#include "Poco/Path.h"
#include <vector>
#include <string>
#include "atFileSystemObject.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

using Poco::Path;
using std::vector;
using std::string;
using dsl::StringList;

class FileFolder;
typedef vector<FileFolder*> FileFolders;

class FileFolder : public FileSystemObject
{
    public:
                            		FileFolder(const Path& name, FileFolder* parent);
        FileFolder*        			getSubFolder(const Path& p);
        FileFolders         		getSubFolders(const Path& subPath = Path("."));
        StringList          		getSubFoldersAsList();
        bool                        isPresent(FileSystemObject* child);
        void 				        addChild(FileSystemObject* child);
        void 				        removeChild(FileSystemObject* child);
        string                      directoryName(int n);

    private:
	    vector<FileSystemObject*> 	mFileFolderContent;
};




#endif

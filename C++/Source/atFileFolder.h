#ifndef atFileFolderH
#define atFileFolderH
#include "Poco/Path.h"
#include <vector>
#include <string>
#include "atFileSystemObject.h"
//---------------------------------------------------------------------------
using Poco::Path;
using std::vector;
using std::string;

class FileFolder;
typedef vector<FileFolder*> FileFolders;

class FileFolder : public FileSystemObject
{
    public:
                            		FileFolder(const Path& name, FileFolder* parent);
        FileFolders         		getSubFolders();
        bool                        isPresent(FileSystemObject* child);
        void 				        addChild(FileSystemObject* child);
        void 				        removeChild(FileSystemObject* child);

    private:
	    vector<FileSystemObject*> 	mFileFolderContent;
};


#endif

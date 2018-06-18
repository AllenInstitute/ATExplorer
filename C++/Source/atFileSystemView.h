#ifndef atFileSystemViewH
#define atFileSystemViewH
#include "Poco/Path.h"
#include <vector>
#include <string>
//---------------------------------------------------------------------------
using Poco::Path;
using std::vector;
using std::string;

class FileFolder;
typedef vector<FileFolder*> FileFolders;
class FileSystemObject
{
    public:
        bool                        isDirectory();
        string                      toString();
        Poco::Path&                 getPath(){return mPath;}

    protected:
        					        FileSystemObject(const Path& name, FileFolder* parent);
    private:
        Path 				        mPath;
        FileFolder*			        mParent;
};

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

class File : public FileSystemObject
{
    public:
        File(const string &name, FileFolder *parent)
        :FileSystemObject(name, parent)
        {}
};

#endif

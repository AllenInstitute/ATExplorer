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

class FileSystemBase
{
    public:
        bool                        isDirectory();
        string                      toString();
        Poco::Path&                 getPath(){return mPath;}

    protected:
        					        FileSystemBase(const Path& name, FileFolder* parent);
    private:
        Path 				        mPath;
        FileFolder*			        mParent;
};

class FileFolder : public FileSystemBase
{
    public:
                            		FileFolder(const Path& name, FileFolder* parent);
        bool                        isPresent(FileSystemBase* child);
        void 				        addChild(FileSystemBase* child);
        void 				        removeChild(FileSystemBase* child);

    private:

	    vector<FileSystemBase*> 	mFileFolderContent;
};

class File : public FileSystemBase
{
    public:
        File(const string &name, FileFolder *parent)
        :FileSystemBase(name, parent)
        {}
};

#endif

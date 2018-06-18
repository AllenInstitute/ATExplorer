#ifndef atFileSystemObjectH
#define atFileSystemObjectH
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

#endif

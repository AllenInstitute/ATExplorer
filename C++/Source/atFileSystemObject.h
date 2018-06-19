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

class FileSystemObject
{
    public:
        bool                        isDirectory();
        virtual string              toString();
        Poco::Path&                 getPath(){return mPath;}
        FileFolder*			        getParent(){ return mParent; }

    protected:
        					        FileSystemObject(const Path& name, FileFolder* parent);
        Path 				        mPath;
        FileFolder*			        mParent;
};


#endif

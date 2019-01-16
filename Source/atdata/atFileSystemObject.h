#ifndef atFileSystemObjectH
#define atFileSystemObjectH
#include "atATDataExporter.h"
#include "Poco/Path.h"
#include <string>
#include "atExplorerObject.h"
//---------------------------------------------------------------------------

namespace at
{

using Poco::Path;
using std::string;

//!Either a folder or a file..
class ATE_DATA FileSystemObject : public ExplorerObject
{
    public:
        bool                        isDirectory();
        virtual string              toString();
        Poco::Path&                 getPath();

    protected:
        					        FileSystemObject(const Path& name);
        Path 				        mPath;
};

}

#endif

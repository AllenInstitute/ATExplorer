#ifndef atFileSystemObjectH
#define atFileSystemObjectH
#include "Poco/Path.h"
#include <vector>
#include <string>
#include "atATObject.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace at
{
using Poco::Path;
using std::vector;
using std::string;
class FileFolder;
using dsl::shared_ptr;

class FileSystemObject : public ATObject
{
    public:
        bool                        isDirectory();
        virtual string              toString();
        Poco::Path&                 getPath();
        FileFolder*    				getParent();

    protected:
        					        FileSystemObject(const Path& name, FileFolder* parent = NULL);
        Path 				        mPath;

                                    //!use shared pointers later on
        FileFolder*      			mParent;
};

}

#endif

#ifndef atFileH
#define atFileH
#include <string>
#include "atFileSystemObject.h"
//---------------------------------------------------------------------------

namespace at
{

using std::string;

class ATE_DATA File : public FileSystemObject
{
    public:
                        File(const string &name)
                        : FileSystemObject(name)
                        {}
};

}
#endif

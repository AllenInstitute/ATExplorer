#ifndef atDataH
#define atDataH
#include "atATObject.h"
#include "Poco/Path.h"
#include "atFileFolder.h"
//---------------------------------------------------------------------------
using Poco::Path;

class ATData : public ATObject
{
    public:
                        	ATData(const Path& bp);
        virtual bool        validate() = 0;

    protected:
        FileFolder     		mBasePath;
};
#endif

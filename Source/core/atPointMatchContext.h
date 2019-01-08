#ifndef atPointMatchContextH
#define atPointMatchContextH
#include "atExplorerObject.h"
#include "atJSMN.h"
//---------------------------------------------------------------------------

namespace at
{

class ATE_CORE PointMatchCollection  : public ExplorerObject
{
    public:
					    	PointMatchCollection(const string& name, int pc);
        					~PointMatchCollection();
        string              getName(){return mName;}
        int		            getPairCount(){return mPairCount;}

    protected:
        string              mName;
        int                 mPairCount;
};

}

#endif

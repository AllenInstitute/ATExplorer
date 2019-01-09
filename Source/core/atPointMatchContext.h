#ifndef atPointMatchContextH
#define atPointMatchContextH
#include "atExplorerObject.h"
#include "atJSMN.h"
//---------------------------------------------------------------------------

namespace at
{

class ATE_CORE PointMatchContext  : public ExplorerObject
{
    public:
					    	PointMatchContext(const string& owner, const string& name, int pc);
        					~PointMatchContext();
        string              getOwner(){return mOwner;}
        void                setOwner(const string& o){mOwner = o;}

        string              getName(){return mName;}
		void                setName(const string& n){mName = n;}

        void	            setPairCount(int pc){mPairCount = pc;}
        int		            getPairCount(){return mPairCount;}

    protected:
        string              mName;
        string              mOwner;
        int                 mPairCount;
};

}

#endif

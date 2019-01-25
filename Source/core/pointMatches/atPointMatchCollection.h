#ifndef atPointMatchCollectionH
#define atPointMatchCollectionH
#include "atRenderObject.h"
#include "atJSMN.h"
#include "atPointMatch.h"
#include "atGenericList.h"
//---------------------------------------------------------------------------

namespace at
{

class ATE_CORE PointMatchCollection : public RenderObject
{
    public:
					    	            PointMatchCollection(const string& owner, const string& name, int pc);
        					            ~PointMatchCollection();
        string                          getOwner(){return mOwner;}
        void                            setOwner(const string& o){mOwner = o;}

        string                          getName(){return mName;}
		void                            setName(const string& n){mName = n;}

        List<PointMatch>	            mPMCollection;
        int                             getCount(){return mPMCollection.count();}
        void                            setCount(int c){mDummyCount = c;}

    protected:
        string                          mName;
        string                          mOwner;
        int                             mDummyCount;

};

}

#endif

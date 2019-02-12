#ifndef atPointMatchCollectionH
#define atPointMatchCollectionH
#include "atRenderObject.h"
#include "atPointMatch.h"
#include "atGenericListOfObjects.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::StringList;

class ATE_CORE PointMatchCollection : public RenderObject
{
    public:
					    	            PointMatchCollection(const string& owner, const string& name, RenderClient* renderService = NULL);
        					            ~PointMatchCollection();
        string                          getOwner(){return mOwner;}
        void                            setOwner(const string& o){mOwner = o;}

        string                          getName(){return mName;}
		void                            setName(const string& n){mName = n;}

        bool                            fetch();

		StringList						getGroupIDs();
		StringList						getPGroupIDs();
		StringList						getQGroupIDs();
        ListOfObjects<PointMatch>       getPQMatches(const string& pGroup, const string& qGroup);
        bool                            deleteCollection();


        ListOfObjects<PointMatch>	    mPMCollection;
        int                             getCount(){return mPMCollection.count();}

    protected:
        string                          mName;
        string                          mOwner;
        StringList                      mGroupIDs;
};

}

#endif

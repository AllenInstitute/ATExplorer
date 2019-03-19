#ifndef atPointMatchCollectionsH
#define atPointMatchCollectionsH
#include "atExplorerObject.h"
#include "atGenericListOfPointers.h"
#include "atGenericListOfObjects.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------
namespace at
{

class PointMatchCollection;

typedef shared_ptr<PointMatchCollection> PointMatchCollectionSP;

class ATE_CORE PointMatchCollections : public ExplorerObject
{
    public:
                        							PointMatchCollections();
                        							~PointMatchCollections();
        void                                        append(PointMatchCollectionSP);
        const PointMatchCollectionSP                getFirst() const;
        PointMatchCollectionSP       		        getFirst();
        const PointMatchCollectionSP   		        getNext() const;
        PointMatchCollectionSP                 		getNext();
        void                                        clear();
        int                                         count() const;
        bool                                        deleteCollection(PointMatchCollection* c);
        bool                                        deleteCollection(const string& o, const string& mc);
    protected:
		ListOfObjects<PointMatchCollectionSP> 		mPointMatchCollections;


};

}


#endif

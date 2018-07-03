#ifndef atATProjectItemsH
#define atATProjectItemsH
#include "atATObject.h"
#include <vector>
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

using std::vector;
using dsl::shared_ptr;

namespace at
{

class ATProjectItem;
typedef shared_ptr<ATProjectItem> ProjItemPtr;

class ATProjectItems : public ATObject
{
    public:
                                            ATProjectItems();
                                            ~ATProjectItems();
        bool                                find(const string& itemName);
        bool                                append(ProjItemPtr item);
        bool                                remove(ProjItemPtr item);
        unsigned int                        size(){return mItems.size();}
        ProjItemPtr		                    operator[](int i);


    protected:
        vector<ProjItemPtr>  				mItems;
        vector<ProjItemPtr>::iterator    	mItemsIter;
};

}

#endif

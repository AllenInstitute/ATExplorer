#pragma hdrstop
#include "atATProjectItems.h"
#include "atATProjectItem.h"
//---------------------------------------------------------------------------
namespace at
{

ATProjectItems::ATProjectItems()
{}

ATProjectItems::~ATProjectItems()
{}

ProjItemPtr ATProjectItems::operator[](int i)
{
    return mItems[i];
}

bool ATProjectItems::append(ProjItemPtr item)
{
    if(!item)
    {
        return false;
    }

    if(!find(item->getProjectName()))
    {
		mItems.push_back(item);
	    return true;
    }
    else
    {
        return false;
    }
}

bool ATProjectItems::find(const string& itemName)
{
    //Compare items to itenName
    for(mItemsIter = mItems.begin(); mItemsIter != mItems.end(); ++mItemsIter)
    {
        if(*mItemsIter)
        {
            if((*mItemsIter)->getProjectName() == itemName)
            {
                return true;
            }
        }
    }
    return false;
}

bool ATProjectItems::remove(ProjItemPtr item)
{
    return true;
}
}


#ifndef atGenericListOfObjectsH
#define atGenericListOfObjectsH
#include "atExplorerObject.h"
#include <list>
//---------------------------------------------------------------------------

namespace at
{

using std::list;

template <typename T>
class ListOfObjects : public ExplorerObject
{
    public:
                                            ListOfObjects(){}
                                            ~ListOfObjects(){}

        void                                append(T obj);
        T*                                  getFirst();
        T*                                  getNext();
        bool                                remove(T item);
        int                                 count();

    protected:
        mutable list< T > 			   		mTheList;
		mutable list< T >::iterator  		mIter;
};

template <typename T>
int ListOfObjects<T>::count()
{
	return mTheList.size();
}

template <typename T>
void ListOfObjects<T>::append(T obj)
{
    mTheList.push_back(obj);
}

template <typename T>
bool ListOfObjects<T>::remove(T item)
{
    mTheList.remove(item);
    return true;
}

template <typename T>
T* ListOfObjects<T>::getFirst()
{
    if(!mTheList.size())
    {
        return NULL;
    }

	mIter = mTheList.begin();
    return &(*mIter);
}

template <typename T>
T* ListOfObjects<T>::getNext()
{
    if(mIter != mTheList.end())
    {
		mIter++;
        if(mIter == mTheList.end())
        {
            return NULL;
        }
        else
        {
	    	return &(*mIter);
        }
    }

    return NULL;
}

}

#endif

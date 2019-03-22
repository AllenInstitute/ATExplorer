#ifndef atGenericListOfPointersH
#define atGenericListOfPointersH
#include "atExplorerObject.h"
#include <list>
//---------------------------------------------------------------------------

namespace at
{

using std::list;

//T is a pointer type
template <typename T>
class ListOfPointers : public ExplorerObject
{
    public:
                                ListOfPointers(){}
                                ~ListOfPointers(){}
        void                    clear();
        void                    append(T obj);
        T                       getFirst() const;
        T                       getNext() const;
        bool                    remove(T item);
        int                     count() const;

    protected:
        list< T > 				mTheList;
        mutable typename list< T >::const_iterator  	mIter;
};

template <typename T>
int ListOfPointers<T>::count() const
{
	return mTheList.size();
}

//template <typename T>
//void ListOfPointers<T>::append(const ListOfPointers<T>& list)
//{
//    T obj = list.getFirst();
//	while(obj)
//    {
//        append(list
//    }
//}

template <typename T>
void ListOfPointers<T>::clear()
{
    for(mIter = mTheList.begin(); mIter != mTheList.end(); ++mIter)
    {
        T item = *mIter;
        delete item;
	}
    mTheList.clear();
}

template <typename T>
void ListOfPointers<T>::append(T obj)
{
    mTheList.push_back(obj);
}

template <typename T>
bool ListOfPointers<T>::remove(T item)
{
    mTheList.remove(item);
    return true;
}

template <typename T>
T ListOfPointers<T>::getFirst() const
{
    if(!mTheList.size())
    {
        return NULL;
    }

	mIter = mTheList.begin();
    return (*mIter);
}

template <typename T>
T ListOfPointers<T>::getNext() const
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
	    	return (*mIter);
        }
    }

    return NULL;
}

}

#endif

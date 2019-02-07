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
        void                    append(const ListOfPointers<T>& obj);
        void                    append(T obj);
        T                       getFirst();
        T                       getNext();
        bool                    remove(T item);
        int                     count();

    protected:
        list< T > 				mTheList;
        list< T >::iterator  	mIter;
};

template <typename T>
int ListOfPointers<T>::count()
{
	return mTheList.size();
}

template <typename T>
void ListOfPointers<T>::append(const ListOfPointers<T>& list)
{
    T obj = list.getFirst();
	while(obj)
    {
        append(list
    }
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
T ListOfPointers<T>::getFirst()
{
    if(!mTheList.size())
    {
        return NULL;
    }

	mIter = mTheList.begin();
    return (*mIter);
}

template <typename T>
T ListOfPointers<T>::getNext()
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

#ifndef atGenericListH
#define atGenericListH
#include "atExplorerObject.h"
#include <list>
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------


namespace at
{

using std::list;

template <typename T>
class ATE_CORE List : public ExplorerObject
{
    public:
                                List(){}
                                ~List(){}
        void                    append(T obj);
        T                       getFirst();
        T                       getNext();
        bool                    remove(T item);

    protected:
        list< T > 				mTheList;
        list< T >::iterator  	mIter;
};

template <typename T>
void List<T>::append(T obj)
{
    mTheList.push_back(obj);
}

template <typename T>
bool List<T>::remove(T item)
{
    mTheList.remove(item);
}

template <typename T>
T List<T>::getFirst()
{
    if(!mTheList.size())
    {
        return T();
    }
	mIter = mTheList.begin();
    return (*mIter);
}

template <typename T>
T List<T>::getNext()
{
    if(mIter != mTheList.end())
    {
		mIter++;
        if(mIter == mTheList.end())
        {
            return T();
        }
        else
        {
	    	return (*mIter);
        }
    }

    return T();
}

}

#endif

#pragma hdrstop
#include "atPointMatchCollections.h"
#include "atPointMatchCollection.h"
//---------------------------------------------------------------------------

namespace at
{

PointMatchCollections::PointMatchCollections()
{}

PointMatchCollections::~PointMatchCollections()
{
    clear();
}

void PointMatchCollections::append(PointMatchCollectionSP pmc)
{
	mPointMatchCollections.append(pmc);
}

int PointMatchCollections::count() const
{
    return mPointMatchCollections.count();
}

const PointMatchCollectionSP PointMatchCollections::getFirst() const
{
    return *(mPointMatchCollections.getFirst());
}

PointMatchCollectionSP PointMatchCollections::getFirst()
{
    return *(mPointMatchCollections.getFirst());
}

const PointMatchCollectionSP PointMatchCollections::getNext() const
{
	const PointMatchCollectionSP* retValue = mPointMatchCollections.getNext();
    if(retValue)
    {
        return *retValue;
    }
    return PointMatchCollectionSP();
}

PointMatchCollectionSP PointMatchCollections::getNext()
{
    return *(mPointMatchCollections.getNext());
}

void PointMatchCollections::clear()
{
    return mPointMatchCollections.clear();
}

bool PointMatchCollections::deleteCollection(const string& o, const string& mc)
{
	PointMatchCollectionSP e = getFirst();
    while(e)
    {
        if(e->getOwner()  == o && e->getName() == mc)
        {
			mPointMatchCollections.remove(e);
            return true;
        }
        e = getNext();
    }
    return false;
}

bool PointMatchCollections::deleteCollection(PointMatchCollection* c)
{
    if(!c)
    {
        return false;
    }

	PointMatchCollectionSP e = getFirst();
    while(e)
    {
        if(e.get() == c)
        {
			mPointMatchCollections.remove(e);
            return true;
        }
        e = getNext();
    }
    return false;
}


}

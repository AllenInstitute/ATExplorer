#pragma hdrstop
#include "atSessions.h"
#include "atSession.h"


namespace at
{
Sessions::Sessions()
{}

Sessions::~Sessions()
{}

Session* Sessions::getFirstSession()
{
    mSessionIterator = begin();
    return *(mSessionIterator);
}

Session* Sessions::getNextSession()
{
	mSessionIterator++;
    if(mSessionIterator != end())
    {
	    return *(mSessionIterator);
    }
    return NULL;
}

}


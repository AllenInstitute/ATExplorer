#pragma hdrstop
#include "atSessions.h"
#include "atSession.h"


namespace at
{
Sessions::Sessions()
{}

Sessions::~Sessions()
{}

void Sessions::clear()
{
    for(int i = 0; i < mSessions.size(); i++)
    {
        delete mSessions[i];
    }
    mSessions.clear();
}

Session* Sessions::getFirstSession()
{
    mSessionIterator = mSessions.begin();
    return *(mSessionIterator);
}

Session* Sessions::getNextSession()
{
	mSessionIterator++;
    if(mSessionIterator != mSessions.end())
    {
	    return *(mSessionIterator);
    }
    return NULL;
}

}


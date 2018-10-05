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
    mSessions.clear();
}

SessionSP Sessions::getFirstSession()
{
    if(mSessions.size() == 0)
    {
        return SessionSP();
    }
    mSessionIterator = mSessions.begin();
    return *(mSessionIterator);
}

SessionSP Sessions::getNextSession()
{
	mSessionIterator++;
    if(mSessionIterator != mSessions.end())
    {
	    return *(mSessionIterator);
    }
    return SessionSP();
}

}


#pragma hdrstop
#include "atSessions.h"
#include "atSession.h"
//---------------------------------------------------------------------------

namespace at
{
Sessions::Sessions()
{}

Sessions::~Sessions()
{}

int Sessions::count()
{
	return mSessions.size();
}

SessionSP Sessions::getSession(const string& lbl)
{
    for(int i = 0; i < mSessions.size(); i++)
    {
        SessionSP s = mSessions[i];
        if(s->getLabel() == lbl)
        {
            return s;
        }
    }
    return SessionSP();
}

bool Sessions::append(SessionSP ns)
{
    //Make sure the session label don't exist
    for(int i = 0; i < mSessions.size(); i++)
    {
        SessionSP s = mSessions[i];
        if(s->getLabel() == ns->getLabel())
        {
            return false;
        }
    }
	mSessions.push_back(ns);
    return true;
}

int Sessions::getNumberOfChannels()
{
    int channelCount(0);
    for(int i = 0; i < mSessions.size(); i++)
    {
        SessionSP s = mSessions[i];
        if(s)
        {
            channelCount += s->getNumberOfChannels();
        }
    }
    return channelCount;
}
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
    if(mSessionIterator != mSessions.end())
    {
		mSessionIterator++;
        if(mSessionIterator == mSessions.end())
        {
            return SessionSP();
        }
        else
        {
	    	return *(mSessionIterator);
        }
    }
    return SessionSP();
}

}


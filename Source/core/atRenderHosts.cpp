#pragma hdrstop
#include "atRenderHosts.h"
#include "atRenderServiceParameters.h"
//---------------------------------------------------------------------------
namespace at
{

RenderHosts::RenderHosts()
{}

RenderHosts::~RenderHosts()
{}

bool RenderHosts::containsHost(const string& name)
{
//    find_if(mHosts.begin(), mHosts.end(),
    return false;
}


bool RenderHosts::addHost(RenderServiceParametersSP h)
{
//    if(containsHost(name))
//    {
//        return false;
//    }
//
//    mHosts.push_back(h);
    return true;
}

bool RenderHosts::removeHost(const string& name)
{
    if(mHosts.size() == 0)
    {
        return false;
    }

    return false;
}

RenderServiceParametersSP RenderHosts::getFirst()
{
    if(mHosts.size() == 0)
    {
        return RenderServiceParametersSP();
    }
    mHostIterator = mHosts.begin();
    return *(mHostIterator);
}

RenderServiceParametersSP RenderHosts::getNext()
{
    if(mHostIterator != mHosts.end())
    {
		mHostIterator++;

        if(mHostIterator == mHosts.end())
        {
            return RenderServiceParametersSP();
        }
        else
        {
	    	return *(mHostIterator);
        }
    }

    return RenderServiceParametersSP();
}

}

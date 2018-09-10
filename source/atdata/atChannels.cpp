#pragma hdrstop
#include "atChannels.h"
//---------------------------------------------------------------------------
namespace at
{

Channels::Channels()
{}

Channels::~Channels()
{}

bool Channels::append(Channel* ch)
{
    push_back(ch);
    return true;
}

Channel* Channels::getFirstChannel()
{
    mChannelIterator = begin();
    return *(mChannelIterator);
}

Channel* Channels::getNextChannel()
{
	mChannelIterator++;
    if(mChannelIterator != end())
    {
	    return *(mChannelIterator);
    }
    return NULL;
}




}

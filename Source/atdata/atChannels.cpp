#pragma hdrstop
#include "atChannels.h"
//---------------------------------------------------------------------------
namespace at
{

Channels::Channels()
{}

Channels::~Channels()
{}

bool Channels::append(ChannelSP ch)
{
    mChannels.push_back(ch);
    return true;
}

StringList Channels::asStringList()
{
    StringList l;
    for(int i = 0; i < mChannels.size(); i++)
	{
        l.append(mChannels[i]->getLabel());
    }
    return l;
}

ChannelSP Channels::getFirstChannel()
{
    if(mChannels.size() == 0)
    {
	    return ChannelSP();
    }

    mChannelIterator = mChannels.begin();
    return *(mChannelIterator);
}

ChannelSP Channels::getNextChannel()
{
	mChannelIterator++;
    if(mChannelIterator != mChannels.end())
    {
	    return *(mChannelIterator);
    }
    return ChannelSP();
}




}

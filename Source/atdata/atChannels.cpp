#pragma hdrstop
#include "atChannels.h"
//---------------------------------------------------------------------------
namespace at
{

Channels::Channels()
{}

Channels::~Channels()
{}

bool Channels::append(ChannelSP new_ch)
{
    //Make sure we don't add a channel twice
    for(int i = 0; i < mChannels.size(); i++)
	{
        ChannelSP c = mChannels[i];
        if(c == new_ch)
        {
            return false;
        }
    }
  	mChannels.push_back(new_ch);
    return true;
}

ChannelSP Channels::getChannel(const string& chLbl)
{
    for(int i = 0; i < mChannels.size(); i++)
	{
        ChannelSP c = mChannels[i];
        if(c->getLabel() == chLbl)
        {
            return c;
        }
    }
    return ChannelSP();
}

ChannelSP Channels::getChannel(ChannelSP ch)
{
    return getChannel(ch->getLabel());
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
    if(mChannelIterator != mChannels.end())
    {
		mChannelIterator++;
        if(mChannelIterator == mChannels.end())
        {
            return ChannelSP();
        }
        else
        {
	    	return *(mChannelIterator);
        }
    }
    return ChannelSP();
}




}

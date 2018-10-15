#pragma hdrstop
#include "atSession.h"
//---------------------------------------------------------------------------
namespace at
{

Session::Session(const string& lbl)
:
mLabel(lbl)
{}

Session::~Session()
{}

string Session::getTypeName() const
{
    return "session";
}

bool Session::operator==(const Session& s) const
{
    //We only need to compare labels
    return mLabel == s.getLabel() ? true : false;
}

int Session::getNumberOfChannels()
{
    return mChannels.count();
}

ChannelSP Session::getChannel(ChannelSP channel)
{
    return mChannels.getChannel(channel);
}

ChannelSP Session::getChannel(const string& channelLabel)
{
    return mChannels.getChannel(channelLabel);
}

bool Session::appendChannel(ChannelSP ch)
{
	return mChannels.append(ch);
}

StringList Session::getChannelLabels()
{
	return mChannels.asStringList();
}

ChannelSP Session::getFirstChannel()
{
    return mChannels.getFirstChannel();
}

ChannelSP Session::getNextChannel()
{
    return mChannels.getNextChannel();
}


}


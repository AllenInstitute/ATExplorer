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

bool Session::operator==(const Session& s) const
{
    //We only need to compare labels
    return mLabel == s.getLabel() ? true : false;
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


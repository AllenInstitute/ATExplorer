#pragma hdrstop
#include "atSession.h"
//---------------------------------------------------------------------------
namespace at
{

Session::Session(const string& lbl)//, Ribbon& r)
:
mLabel(lbl)//,
//mRibbon(r)
{}

Session::~Session()
{}

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


#pragma hdrstop
#include "atSession.h"
//---------------------------------------------------------------------------
namespace ate
{

Session::Session(const string& lbl)//, Ribbon& r)
:
mLabel(lbl)//,
//mRibbon(r)
{}

Session::~Session()
{}

bool Session::appendChannel(Channel* ch)
{
	return mChannels.append(ch);
}

Channel* Session::getFirstChannel()
{
    return mChannels.getFirstChannel();
}

Channel* Session::getNextChannel()
{
    return mChannels.getNextChannel();
}


}


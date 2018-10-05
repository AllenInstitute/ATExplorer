#pragma hdrstop
#include "atChannel.h"
#include "atSession.h"
//---------------------------------------------------------------------------

namespace at
{

Channel::Channel(const string& lbl, Session& s)
:
mLabel(lbl),
mSession(s)
{}

Channel::~Channel()
{}

bool Channel::operator==(const Channel& c) const
{
    return (mLabel == c.getLabel() && mSession == c.mSession) ? true : false;
}
}

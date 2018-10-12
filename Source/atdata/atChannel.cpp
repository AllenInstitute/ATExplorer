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

const string Channel::getTypeName() const
{
    return "channel";
}

bool Channel::operator==(const Channel& c) const
{
    bool value = (mLabel == c.getLabel() && mSession == c.mSession) ? true : false;
    return value;
}
}

#pragma hdrstop
#include "atChannels.h"
//---------------------------------------------------------------------------
namespace at
{

Channels::Channels()
{}

Channels::~Channels()
{}

bool Channels::append(const Channel& ch)
{
    push_back(ch);
    return true;
}
}

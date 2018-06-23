#pragma hdrstop
#include "atChannel.h"
#include "atSession.h"
//---------------------------------------------------------------------------

namespace at
{

Channel::Channel(const Session& s, const string& lbl)
:
mLabel(lbl),
mSession(s)//,
//mTiles(this)
{}


Channel::~Channel()
{}

Channel& Channel::operator=(const Channel& rhs)
{
    this->mLabel = rhs.mLabel;
    this->mSession = rhs.mSession;
    return *this;
}

//Channel::Channel(const Channel& c)
//{
//
//}

//bool Channel::addTile(Tile* aTile)
//{
//    mTiles.append(aTile);
//    return true;
//}
}

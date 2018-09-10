#pragma hdrstop
#include "atChannel.h"
#include "atTiles.h"
#include "atSession.h"
//---------------------------------------------------------------------------

namespace ate
{

Channel::Channel(const string& lbl, Session* s)
:
mLabel(lbl),
mSession(s),
mTiles(*this)
{}

Channel::~Channel()
{}

bool Channel::appendTile(Tile* t)
{
    //Populate the map with tile paths
    mTiles.append(t);

}


}

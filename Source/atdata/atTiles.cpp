#pragma hdrstop
#include "atTiles.h"
#include "atTile.h"
//---------------------------------------------------------------------------

namespace ate
{

Tiles::Tiles(const Channel& s)
:
mChannel(&s)
{}

Tiles::~Tiles()
{}

bool Tiles::append(Tile* t)
{
    mTiles[t->getID()] = t;
    return true;
}

}

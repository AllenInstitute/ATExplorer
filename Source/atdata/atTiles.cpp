#pragma hdrstop
#include "atTiles.h"
#include "atTile.h"
//---------------------------------------------------------------------------

namespace at
{

Tiles::Tiles(const Channel& s)
:
mChannel(&s)
{}

Tiles::~Tiles()
{}

bool Tiles::append(TileSP t)
{
    mTiles[t->getID()] = t;
    return true;
}

}

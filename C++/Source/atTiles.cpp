#pragma hdrstop
#include "atTiles.h"
#include "atTile.h"
//---------------------------------------------------------------------------

namespace at
{

Tiles::Tiles(const Session& s)
:
mSession(s)
{}

Tiles::~Tiles()
{}


bool Tiles::append(Tile* t)
{
//    push_back(t);
    return true;
}

}

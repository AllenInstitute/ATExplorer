#pragma hdrstop
#include "atTile.h"
//---------------------------------------------------------------------------
namespace at
{

Tile::Tile(int id, Section& s, Channel& c)
:
mID(id),
mSection(s),
mChannel(c)
{}

Tile::~Tile()
{}

bool Tile::assignPath(Path& p, bool checkOnDisk)
{
    mRawDataPath = p;

}
}


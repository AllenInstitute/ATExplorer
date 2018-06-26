#pragma hdrstop
#include "atTile.h"
#include "atATIFDataUtils.h"
//---------------------------------------------------------------------------
namespace at
{

Tile::Tile(Channel& c, Section& s, int tileID, const Path& p)
:
mSection(s),
mChannel(c),
mRawDataPath(p),
mID(tileID)
{
	mID = getTileID(mRawDataPath.getFileName());
}

Tile::~Tile()
{}

bool Tile::assignPath(Path& p, bool checkOnDisk)
{
    mRawDataPath = p;

}
}


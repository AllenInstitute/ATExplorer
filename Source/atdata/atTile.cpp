#pragma hdrstop
#include "atTile.h"
#include "atATDataUtils.h"
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

int Tile::getID()
{
	return mID;
}

Path Tile::getPath()
{
	return mRawDataPath;
}

const Channel& Tile::getChannel()
{
	return mChannel;
}

const Section& Tile::getSection()
{
	return mSection;
}

bool Tile::assignPath(Path& p, bool checkOnDisk)
{
    mRawDataPath = p;
    return true;
}
}


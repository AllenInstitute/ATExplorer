#pragma hdrstop
#include "atTiles.h"
#include "atTile.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

namespace at
{

using namespace dsl;

Tiles::Tiles(const Channel& s)
:
mChannel(s)
{}

Tiles::~Tiles()
{}

bool Tiles::append(TileSP t)
{
    if(t->getChannel() == mChannel)
    {
	    mTiles[t->getID()] = t;
        return true;
    }

    Log(lError) << "Wrong tile in Tiles::append(...)";

    return false;
}

const Channel& Tiles::getChannel() const
{
	return mChannel;
}

int Tiles::count()
{
	return mTiles.size();
}

}

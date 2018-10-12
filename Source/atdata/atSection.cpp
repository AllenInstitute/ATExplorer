#pragma hdrstop
#include "atSection.h"
#include "atTiles.h"
//---------------------------------------------------------------------------

namespace at
{

Section::Section(int id, const Ribbon& r)
:
mID(id),
mRibbon(r)
{}

Section::~Section()
{}

const string Section::getTypeName() const
{
    return "section";
}

void Section::addTile(TileSP tile)
{
    //Get Tiles container for the tiles channel. If it does not exists, create a new one
    Channel ch = tile->getChannel();

    TilesSP tiles;
    for(int i = 0; i < mTiles.size(); i++)
    {
        if(mTiles[i]->getChannel() == ch)
        {
            tiles = mTiles[i];
            break;
        }
    }

    if(!tiles)
    {
	    tiles = TilesSP(new Tiles(tile->getChannel()));
        mTiles.push_back(tiles);
    }
    tiles->append(tile);

}

TilesSP Section::getTiles(const ChannelSP& ch)
{
    for(int i = 0; i < mTiles.size(); i++)
    {
        if(mTiles[i]->getChannel() == *(ch.get()))
        {
            return mTiles[i];
        }
    }
    return TilesSP();
}

int Section::getTotalNumberOfTiles()
{
    int nrOfTiles(0);
    for(int i = 0; i < mTiles.size(); i++)
    {
    	nrOfTiles += mTiles[i]->count();
    }
    return nrOfTiles;
}

int Section::getNumberOfTiles(const ChannelSP& ch)
{
	TilesSP tiles = getTiles(ch);
    if(tiles)
    {
    	return tiles->count();
    }
    else
    {
        return 0;
    }
}

}



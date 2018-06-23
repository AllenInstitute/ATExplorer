#pragma hdrstop
#include "atSection.h"

namespace at
{

Section::Section(int id, const Ribbon& r)
:
mID(id),
mRibbon(r)
{}

Section::~Section()
{}

int Section::getNumberOfTiles() const
{
//    return size();
}

//bool Section::appendTile(Tile* tile)
//{
//    this->push_back(tile);
//    return false;
//}

}



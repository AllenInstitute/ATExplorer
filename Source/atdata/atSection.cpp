#pragma hdrstop
#include "atSection.h"
#include "atTiles.h"
#include "atChannel.h"

namespace ate
{

Section::Section(int id, const Ribbon& r)
:
mID(id),
mRibbon(r)
{}

Section::~Section()
{}

Tiles& Section::getTiles(Channel& ch)
{
    return ch.getTiles();
}

}



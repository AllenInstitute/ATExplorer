#pragma hdrstop
#include "atSection.h"

namespace at
{

Section::Section(int id)
:
mID(id)
{}

Section::~Section()
{}

int Section::getNumberOfTiles()
{
    return size();
}
}



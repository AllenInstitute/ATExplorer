#pragma hdrstop
#include "atPointMatch.h"
//---------------------------------------------------------------------------
namespace at
{

PointMatch::PointMatch(const PointMatchPoint& p, const PointMatchPoint& q)
:
mP(p),
mQ(q)
{}

PointMatch::~PointMatch()
{}

}


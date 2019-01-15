#pragma hdrstop
#include "atPointMatchPoint.h"
//---------------------------------------------------------------------------
namespace at
{

PointMatchPoint::PointMatchPoint(const string& gID, PointMatchGroup g, double x, double y, double w, const PointMatchPoint* p2)
:
mGroupID(gID),
mPointMatchGroup(g),
mX(x),
mY(y),
mWeight(w),
mCorrespondingPoint(p2)
{}

PointMatchPoint::~PointMatchPoint()
{}

void PointMatchPoint::assignCorrespondingPoint(const PointMatchPoint& p2)
{
    mCorrespondingPoint = &p2;
}

const PointMatchPoint* PointMatchPoint::getCorrespondingPoint()
{
    return mCorrespondingPoint;
}

}


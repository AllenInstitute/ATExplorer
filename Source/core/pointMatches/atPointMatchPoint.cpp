#pragma hdrstop
#include "atPointMatchPoint.h"
//---------------------------------------------------------------------------
namespace at
{

PointMatchPoint::PointMatchPoint(const string& gID, PointMatchGroup g, const Point2D& p, double w, const PointMatchPoint* p2)
:
mGroupID(gID),
mPointMatchGroup(g),
mPoint(p),
mWeight(w),
mCorrespondingPoint(p2)
{}

PointMatchPoint::PointMatchPoint(const PointMatchPoint& p)
{
    mGroupID = p.mGroupID;
    mPointMatchGroup = p.mPointMatchGroup;
    mPoint = p.mPoint;
    mWeight = p.mWeight;
    mCorrespondingPoint = p.mCorrespondingPoint;
}

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


#pragma hdrstop
#include "atPoint2D.h"
#include <cmath>
//---------------------------------------------------------------------------

namespace at
{
using namespace std;
Point2D::Point2D(double x, double y)
:
mX(x),
mY(y)
{}

double Point2D::x()
{
	return mX;
}

double Point2D::y()
{
	return mY;
}

double Point2D::distance(const Point2D& other)
{
	double xd = mX - other.mX;
    double yd = mY - other.mY;
    return sqrt(xd*xd + yd*yd);
}

// Add or subtract two points.
Point2D Point2D::add(const Point2D& b)
{
	return Point2D(mX + b.mX, mY + b.mY);
}

Point2D Point2D::subtract(const Point2D& b)
{
	return Point2D(mX - b.mX, mY - b.mY);
}

// Move the existing point.
void Point2D::move(double a, double b)
{
    mX += a;
    mY += b;
}

void Point2D::print(ostream &o)
{
	o << "(" << mX << "," << mY << ")";
}

}
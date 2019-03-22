#ifndef atPoint2DH
#define atPoint2DH
#include "atExplorerObject.h"
#include <ostream>
//---------------------------------------------------------------------------

using std::ostream;
namespace at
{

// Simple class to represent a 2D point.
class ATE_CORE Point2D : public ExplorerObject
{
    public:
                                                        // Constructor uses default arguments to allow calling with zero, one,
                                                        // or two values.
                                                        Point2D(double x = 0.0, double y = 0.0);
            double                                      x();
            double                                      y();

            double 										distance(const Point2D& other);

            											//Add or subtract two points.
            Point2D                                     add(const Point2D& b);
            Point2D                                     subtract(const Point2D& b);

            											//"Move" existing point.
            void 										move(double a, double b);

            											// Print the point on the stream.
            void 									    print(ostream &o);

    protected:
            double 							            mX;
            double 							            mY;

};

}
#endif

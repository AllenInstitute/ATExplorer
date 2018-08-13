#ifndef atRegionOfInterestH
#define atRegionOfInterestH
#include <cstdlib>
#include <string>
//---------------------------------------------------------------------------

using std::abs;
using std::string;

//!TODO, write code to update the box when something changes..
class PACKAGE RegionOfInterest
{
	public:
	    								RegionOfInterest(double x = 0, double y = 0, double width = 0, double height = 0, double scale = 1);
	    								RegionOfInterest(const string& str);
		void							setX1(double x);
        double							getX1();
		void							setX2(double x);

        double							getX2();
		void							setWidth(double w);
        double							getWidth();

		void							setY1(double y);
        double							getY1();

		void							setY2(double y);
        double							getY2();

		void							setHeight(double h);
        double							getHeight();

        void							setZ(double z);
        double							getZ();

        void							setScale(double s);
        double							getScale();

        void 							zoom(double persent);

	protected:
    	int								mZ;
	    double                          mX1;
    	double                          mY1;
	    double                          mWidth;
    	double                          mHeight;
        double							mScale;

};

#endif

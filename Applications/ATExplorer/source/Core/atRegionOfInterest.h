#ifndef atRegionOfInterestH
#define atRegionOfInterestH
#include <cstdlib>
#include <string>
#include <boost/function.hpp>
//---------------------------------------------------------------------------

using std::abs;
using std::string;

//!TODO, write code to update the box when something changes..
typedef boost::function<void(void*, void*)> OnChangeFnc;
class PACKAGE RegionOfInterest
{
	public:
	    								RegionOfInterest(double x = 0, double y = 0, double width = 0, double height = 0, double scale = 1);
	    								RegionOfInterest(const string& str);
	    								RegionOfInterest(const RegionOfInterest& cpme);
        RegionOfInterest&               operator=(const RegionOfInterest& rhs);


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
        void                            assignOnChangeCallback(OnChangeFnc f);

	protected:
    	int								mZ;
	    double                          mX;
    	double                          mY;
	    double                          mWidth;
    	double                          mHeight;
        double							mScale;
        OnChangeFnc                     onChange;

};

#endif

#ifndef atRegionOfInterestH
#define atRegionOfInterestH
#include "atExplorerObject.h"
#include <cstdlib>
#include <string>
#include <boost/function.hpp>
#include "tinyxml2/tinyxml2.h"
//---------------------------------------------------------------------------

namespace dsl
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLElement;
    using tinyxml2::XMLNode;
}

namespace at
{

using std::abs;
using std::string;

//!TODO, write code to update the box when something changes..
typedef boost::function<void(void*, void*)> OnChangeFnc;

//---------------------------------------------------------------------------
class ATE_CORE RegionOfInterest : public ExplorerObject
{
	public:
	    								RegionOfInterest(int x = 0, int y = 0, int width = 0, int height = 0, double scale = 1);
	    								RegionOfInterest(const string& str, double scale = 1);
	    								RegionOfInterest(const RegionOfInterest& cpme);
        RegionOfInterest&               operator=(const RegionOfInterest& rhs);

        string                          getFolderName() const;
		void							setX1(int x);
        int								getX1() const;
		void							setX2(int x);

        int								getX2() const;
		void							setWidth(int w);
        int								getWidth() const;

		void							setY1(int y);
        int								getY1() const;

		void							setY2(int y);
        int								getY2() const;

		void							setHeight(int h);
        int  							getHeight() const;

        void							setZ(int z);
        int 							getZ() const;

        void							setScale(double s);
        double							getScale() const;

        void 							zoom(double persent);
        void                            assignOnChangeCallback(OnChangeFnc f);
        dsl::XMLElement*        		addToXMLDocumentAsChild(dsl::XMLDocument& doc, dsl::XMLNode* docRoot);
		bool 							loadFromXML(dsl::XMLNode* node);

	protected:
    	int								mZ;
	    double                          mX;
    	double                          mY;
	    int                             mWidth;
    	int                             mHeight;
        double							mScale;
        OnChangeFnc                     onChange;
};

}
#endif

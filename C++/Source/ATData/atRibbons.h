#ifndef atRibbonsH
#define atRibbonsH
#include "atATObject.h"
#include <vector>
//---------------------------------------------------------------------------

namespace at
{

using std::vector;
class Ribbon;

//!The Ribbons class is a container for AT Ribbons
class Ribbons : public vector<Ribbon*>, public ATObject
{
	public:
                                        Ribbons();
        virtual            	            ~Ribbons();
        Ribbon*                         getRibbon(int i);
        Ribbon*                        	getFirstRibbon();
        Ribbon*                        	getNextRibbon();

        int                             count();

    protected:
        vector<Ribbon*>::iterator   	mRibbonIterator;
};

}
#endif

#ifndef atRibbonsH
#define atRibbonsH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"
//---------------------------------------------------------------------------

namespace ate
{

using std::vector;
class Ribbon;

//!The Ribbons class is a container for AT Ribbons
class ATE_DATA Ribbons : public vector<Ribbon*>, public ExplorerObject
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

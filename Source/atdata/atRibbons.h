#ifndef atRibbonsH
#define atRibbonsH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"
//---------------------------------------------------------------------------

namespace at
{

using std::vector;
class Ribbon;

//!The Ribbons class is a container for AT Ribbons
class ATE_DATA Ribbons : public ExplorerObject
{
	public:
                                        Ribbons();
        virtual            	            ~Ribbons();
        Ribbon*                         operator[](int i);
        Ribbon*                         getRibbon(int i);
        Ribbon*                        	getFirstRibbon();
        Ribbon*                        	getNextRibbon();
        void                            append(Ribbon* r);

        int                             count();

    protected:
        vector<Ribbon*>::iterator   	mRibbonIterator;
        vector<Ribbon*>                 mRibbons;
};

}
#endif

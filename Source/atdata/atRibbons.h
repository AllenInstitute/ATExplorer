#ifndef atRibbonsH
#define atRibbonsH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace at
{

using std::vector;
class Ribbon;

typedef shared_ptr<Ribbon> RibbonSP;

//!The Ribbons class is a container for AT Ribbons
class ATE_DATA Ribbons : public ExplorerObject
{
	public:
                                                    Ribbons();
        virtual            	                        ~Ribbons();
        RibbonSP                                    operator[](int i);
        RibbonSP                                    getRibbon(int i);
        RibbonSP                                    getFirstRibbon();
        RibbonSP                                    getNextRibbon();
        void                                        append(RibbonSP r);

        void                                        clear();
        int                                         count();

    protected:
        vector<RibbonSP>::iterator   	            mRibbonIterator;
        vector<RibbonSP>           		            mRibbons;
};

}
#endif

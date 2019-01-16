#ifndef atPointMatchH
#define atPointMatchH
#include "atExplorerObject.h"
#include "atPointMatchPoint.h"
//---------------------------------------------------------------------------

namespace at
{

//!A pointmatch is a pair of xyz coordinates (in the same coordinate system)
//!matching one feature in one image to the same (ideally) feature in another image
class ATE_CORE PointMatch : public ExplorerObject
{
    public:
    						        PointMatch(const PointMatchPoint& p, const PointMatchPoint& q);
 					                ~PointMatch();

        const PointMatchPoint&	    getSourcePoint();
        const PointMatchPoint&   	getDestinationPoint();

    protected:
                                    //!The 'source' point
        PointMatchPoint             mP;

                                    //!The 'destination' point
		PointMatchPoint             mQ;

};

}

#endif

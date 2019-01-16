#ifndef atPointMatchPointH
#define atPointMatchPointH
#include "atExplorerObject.h"
//---------------------------------------------------------------------------
namespace at
{


//!A PointMatchPoint is part of a PointMatch pair of points
class ATE_CORE PointMatchPoint : public ExplorerObject
{
    enum PointMatchGroup {pGroup, qGroup};
    public:
                                    PointMatchPoint(const string& groupID, PointMatchGroup group, double x, double y, double w, const PointMatchPoint* p2 = NULL);
        void                        assignCorrespondingPoint(const PointMatchPoint& p2);
    	const PointMatchPoint*      getCorrespondingPoint();

                                    ~PointMatchPoint();

    protected:
        string                      mGroupID;
        PointMatchGroup             mPointMatchGroup;
        double                      mWeight;
        double                      mX;
        double                      mY;
        const PointMatchPoint*      mCorrespondingPoint;
};

}

#endif

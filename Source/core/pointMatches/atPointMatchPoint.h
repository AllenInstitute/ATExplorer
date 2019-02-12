#ifndef atPointMatchPointH
#define atPointMatchPointH
#include "atExplorerObject.h"
#include "atPoint2D.h"
//---------------------------------------------------------------------------
namespace at
{

//!A PointMatchPoint is part of a PointMatch pair of points
class ATE_CORE PointMatchPoint : public ExplorerObject
{
    public:
	     enum PointMatchGroup {pGroup, qGroup};
                                    PointMatchPoint(const string& groupID, PointMatchGroup group, const Point2D& p, double w, const PointMatchPoint* p2 = NULL);
                                    PointMatchPoint(const PointMatchPoint& pToCopy);
        void                        assignCorrespondingPoint(const PointMatchPoint& p2);
    	const PointMatchPoint*      getCorrespondingPoint();

                                    ~PointMatchPoint();

    protected:
        string                      mGroupID;
        PointMatchGroup             mPointMatchGroup;
        double                      mWeight;
        Point2D                     mPoint;
        const PointMatchPoint*      mCorrespondingPoint;
};

}

#endif

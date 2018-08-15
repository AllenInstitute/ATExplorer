#ifndef atROIHistoryH
#define atROIHistoryH
#include "atRenderClient.h"
#include <deque>
//---------------------------------------------------------------------------

using std::deque;
class PACKAGE ROIHistory
{
	public:
    								        ROIHistory();
    								        ~ROIHistory();
		void						        clear();

		void						        add(RegionOfInterest& rb);
		void						        insert(RegionOfInterest& rb);

		RegionOfInterest*					current();
		RegionOfInterest*					first();
		RegionOfInterest*					last();
        RegionOfInterest*					next();
        RegionOfInterest*					previous();


    private:
    	deque<RegionOfInterest> 			mHistory;
        deque<RegionOfInterest>::iterator	mCurrent;
};
#endif

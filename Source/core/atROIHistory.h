#ifndef atROIHistoryH
#define atROIHistoryH
#include "atExplorerCoreExporter.h"
#include "atRenderClient.h"
#include <deque>
//---------------------------------------------------------------------------

namespace at
{
using std::deque;
class ATE_CORE ROIHistory
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
}
#endif

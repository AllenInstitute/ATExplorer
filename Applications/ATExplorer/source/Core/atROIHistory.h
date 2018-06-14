#ifndef atROIHistoryH
#define atROIHistoryH
#include "atRenderClient.h"
#include <deque>
//---------------------------------------------------------------------------

using std::deque;
class ROIHistory
{
	public:
    								ROIHistory();
    								~ROIHistory(){}
		void						clear();

		void						add(RenderBox& rb);
		void						insert(RenderBox& rb);

		RenderBox*					current();
		RenderBox*					first();
		RenderBox*					last();
        RenderBox*					next();
        RenderBox*					previous();


    private:
    	deque<RenderBox> 			mHistory;
        deque<RenderBox>::iterator	mCurrent;
};
#endif

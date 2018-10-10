#ifndef atPopulateATDataThreadH
#define atPopulateATDataThreadH
#include "dslThread.h"
#include "dslStringList.h"
#include "atATData.h"
#include <boost/function.hpp>
#include "atExplorerObject.h"
//---------------------------------------------------------------------------


namespace at
{
using dsl::StringList;
using dsl::Thread;
typedef boost::function<void(void*, void*)> FITCallBack;
typedef shared_ptr<ATData> ATDataSP;

class ATE_DATA PopulateATDataThread : public dsl::Thread, public ExplorerObject
{
	public:
							                PopulateATDataThread(ATDataSP d);
        void                                setData(shared_ptr<ATData> d);
        void                                assignCallBacks(FITCallBack one, FITCallBack two, FITCallBack three);
		virtual void                        run();
        void				                worker();

	private:
        shared_ptr<ATData>	                mTheData;
        FITCallBack                         onEnter;
        FITCallBack                         onProgress;
        FITCallBack                         onExit;
};

}
#endif

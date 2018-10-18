#ifndef atCreateATIFDataStateTablesThreadH
#define atCreateATIFDataStateTablesThreadH
#include "dslThread.h"
#include "dslStringList.h"
#include "atATIFData.h"
#include <boost/function.hpp>
#include "atExplorerObject.h"
//---------------------------------------------------------------------------


namespace at
{
using dsl::StringList;
using dsl::Thread;
typedef boost::function<void(void*, void*)> FITCallBack;

class ATE_DATA CreateATIFDataStateTablesThread : public dsl::Thread, public ExplorerObject
{
	public:
							                CreateATIFDataStateTablesThread(ATIFData& d);
        void                                assignCallBacks(FITCallBack one, FITCallBack two, FITCallBack three);
		virtual void                        run();
        void				                worker();

	private:
        ATIFData&		   	                mTheData;
        FITCallBack                         onEnter;
        FITCallBack                         onProgress;
        FITCallBack                         onExit;
};

}
#endif

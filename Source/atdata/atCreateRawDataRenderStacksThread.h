#ifndef atCreateRawDataRenderStacksThreadH
#define atCreateRawDataRenderStacksThreadH
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


class ATE_DATA CreateRawDataRenderStacksThread : public dsl::Thread, public ExplorerObject
{
	typedef boost::function<void(void*, void*, void*)> FITCallBack;
	public:
							                CreateRawDataRenderStacksThread(ATIFData& d);
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

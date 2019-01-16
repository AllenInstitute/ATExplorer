#ifndef atATIFDataProcessThreadH
#define atATIFDataProcessThreadH
#include "dslThread.h"
#include "atATIFData.h"
#include <boost/function.hpp>
#include "atExplorerObject.h"
//---------------------------------------------------------------------------


namespace at
{

using dsl::Thread;
using dsl::gEmptyString;
class DockerContainer;

//!baseclass for ATIFdata processing threads
class ATE_DATA ATIFDataProcessThread : public dsl::Thread, public ExplorerObject
{
	public:
		typedef boost::function<void(void*, void*, void*)> CallBack;

							                ATIFDataProcessThread(ATIFData& data, DockerContainer* dc, const string& rh = gEmptyString);
		virtual				                ~ATIFDataProcessThread();
        void                                assignCallBacks(CallBack one, CallBack two, CallBack three);
		virtual void                        run() = 0;

	protected:
        ATIFData&		   	                mTheData;
        CallBack                         	onEnter;
        CallBack                         	onProgress;
        CallBack                         	onExit;
        DockerContainer*                    mDockerContainer;
        string                              mRenderHost;
};

}
#endif

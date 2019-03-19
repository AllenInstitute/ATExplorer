#pragma hdrstop
#include "atATIFDataProcessThread.h"
#include "dslLogger.h"
#include "Poco/File.h"
#include "dslStringUtils.h"
#include "dslFileUtils.h"
#include "atATEExceptions.h"
#include "atStringUtils.h"
//---------------------------------------------------------------------------

namespace at
{
using namespace dsl;

ATIFDataProcessThread::ATIFDataProcessThread(ATIFData& d, DockerContainer* dc,  const string& rh)
:
mTheData(d),
mDockerContainer(dc),
mRenderHost(rh),
onEnter(nullptr),
onProgress(nullptr),
onExit(nullptr)
{}

ATIFDataProcessThread::~ATIFDataProcessThread()
{}

void ATIFDataProcessThread::assignCallBacks(CallBack one, CallBack two, CallBack three)
{
    onEnter 	= one;
    onProgress 	= two;
    onExit 		= three;
    mTheData.assignOnPopulateCallbacks(one, two, three);
}

}

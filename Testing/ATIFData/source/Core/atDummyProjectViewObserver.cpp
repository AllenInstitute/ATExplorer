#pragma hdrstop
#include "atDummyProjectViewObserver.h"
#include "atRenderProjectView.h"
#include "dslLogger.h"
#include "atProjectObservers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace at
{

using namespace dsl;

DummyProjectViewObserver::DummyProjectViewObserver(ProjectObservers& o, RenderProjectView& rpv)
:
Observer(rpv.getSubject()),
mHost(o),
mRPV(rpv)
{
	observe(rpv.getSubject());
}

DummyProjectViewObserver::~DummyProjectViewObserver()
{}


RenderProjectView* DummyProjectViewObserver::getView()
{
    return &mRPV;
}

void DummyProjectViewObserver::update(Subject* theChangedSubject, SubjectEvent se)
{
	if(se == SubjectEvent::SubjectBeingDestroyed)
    {
        //remove from Host..
        Log(lInfo) << "Subject being destroyed..";
//        mHost.removeObserver(this);
    }
}

}
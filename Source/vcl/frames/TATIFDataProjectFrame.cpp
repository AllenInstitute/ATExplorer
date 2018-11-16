#include <vcl.h>
#pragma hdrstop
#include "TATIFDataProjectFrame.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
#include "Poco/Path.h"
#include "atdata/atATIFData.h"
#include "atdata/atRibbon.h"
#include "atdata/atSession.h"
#include "atExceptions.h"
#include "TCreateATIFDataStateTablesForm.h"
#include "TCreateACQRenderStacksForm.h"
#include "TCreateMediansForm.h"
#include "atATExplorer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TATIFDataProjectFrame *ATIFDataProjectFrame;
using namespace dsl;
using namespace at;
using namespace Poco;

static int frameNr(0);

//---------------------------------------------------------------------------
__fastcall TATIFDataProjectFrame::TATIFDataProjectFrame(ATExplorer& e, ATIFDataProject& dp, TComponent* Owner)
	: TFrame(Owner),
    mExplorer(e),
    mProject(dp),
	mPopulateDataThread(dp.mATIFData)
{
    this->Name = string("ATIFDataFrame_" +  dsl::toString(frameNr++)).c_str();
    populate();
}

//---------------------------------------------------------------------------
void TATIFDataProjectFrame::populate()
{
    DataRootFolderE->setValue(mProject.getDataRootFolder());

    //Fill out render and docker backends
    RenderPythonContainersCB->Clear();
    DockerContainer* c =  mExplorer.getFirstDockerContainer();
    while(c)
    {
		RenderPythonContainersCB->AddItem(c->getName().c_str(), (TObject*) c);
        c = mExplorer.getNextDockerContainer();
    }

    //Check if the current project has a selected RenderPythonContainer..
	//    if(mProject.g

    RenderServicesCB->Clear();
    RenderServiceParameters* rs =  mExplorer.getFirstRenderService();
    while(rs)
    {
		RenderServicesCB->AddItem(rs->getName().c_str(), (TObject*) rs);
        rs = mExplorer.getNextRenderService();
    }
}

//---------------------------------------------------------------------------
void __fastcall TATIFDataProjectFrame::ScanDataBtnClick(TObject *Sender)
{
    if(ScanDataBtn->Caption == "Scan Data")
    {
        //Pretty ugly
        if(mProject.getDataRootFolder().size() && mProject.getDataRootFolder()[mProject.getDataRootFolder().size() -1] != gPathSeparator)
        {
            mProject.setDataRootFolder(mProject.getDataRootFolder() + gPathSeparator);
        }

        mProject.mATIFData.reset();
        mPopulateDataThread.assignCallBacks(onThreadEnter,onThreadProgress, onThreadExit);
        mPopulateDataThread.start(true);
    }
    else
    {
        mPopulateDataThread.stop();
    }
}

void TATIFDataProjectFrame::onThreadEnter(void* arg1, void* arg2, void* arg3)
{
    //Setup progress bar
    if(arg1)
    {
    	ATIFData* data = (ATIFData*) arg1;
        if(!data->getRibbonsDataFolder())
        {
            Log(lError) << "This data have no RibbonsFolder!";
            mPopulateDataThread.stop();
            return;
        }
        int nrOfFiles = data->getRibbonsDataFolder()->getFolderInfo().NrOfFiles;
        PopulatePB->Max = nrOfFiles;
    }

	ScanDataBtn->Caption = "Stop Scan";
}

//A way to use TThread::Synchronize with arguments
struct TLocalArgs1
{
    ATIFData* data;
    TATIFDataProjectFrame* frame;

    void __fastcall sync()
    {
        frame->NrOfRibbonsLbl->Caption 		= IntToStr(data->getNumberOfRibbons());
        frame->NrOfSectionsLbl->Caption 	= IntToStr(data->getNumberOfSections());
        frame->NrOfTilesLbl->Caption 		= IntToStr(data->getNumberOfTiles());
        frame->NrOfSessionsLbl->Caption     = IntToStr(data->getNumberOfSessions());
        frame->NrOfChannelsLbl->Caption     = IntToStr(data->getNumberOfChannels());

        int nrOfStateTables = data->getNumberOfRibbons() * data->getNumberOfSessions() * data->getNumberOfSections();
        frame->StateTablesLbl->Caption = IntToStr(data->getNumberOfStateTables()) + " (" + IntToStr(nrOfStateTables) + ")";
        frame->PopulatePB->Position 		= data->getNumberOfTiles();
    }
};

void TATIFDataProjectFrame::onThreadProgress(void* arg1, void* arg2, void* arg3)
{
    if(arg1)
    {
    	ATIFData* data = (ATIFData*) arg1;

        TLocalArgs1 Args;
        Args.data = data;
        Args.frame = this;
        TThread::Synchronize(NULL, &Args.sync);
    }
}

void TATIFDataProjectFrame::onThreadExit(void* arg1, void* arg2, void* arg3)
{
    if(arg1)
    {
    	ATIFData* data = (ATIFData*) arg1;

        TLocalArgs1 Args;
        Args.data = data;
        Args.frame = this;
        TThread::Synchronize(NULL, &Args.sync);
    }
	ScanDataBtn->Caption = "Scan Data";
    mProject.notifyObservers(UpdateRepresentation);
}

//---------------------------------------------------------------------------
void __fastcall TATIFDataProjectFrame::CreateStateTablesBtnClick(TObject *Sender)
{
    const TButton* b = dynamic_cast<TButton*>(Sender);

    if(b == CreateStateTablesBtn)
    {
        //Open Generate state tables form..
        unique_ptr<TCreateATIFDataStateTablesForm> f (new TCreateATIFDataStateTablesForm(mProject.mATIFData, gATExplorer.mRenderPythonApps, this->Owner));
        f->ShowModal();
    }
    else if(b == CreateRenderStacksBtn)
    {
        unique_ptr<TCreateACQRenderStacksForm> f (new TCreateACQRenderStacksForm(mProject.mATIFData, gATExplorer.getFirstDockerContainer(), "", this->Owner));
        f->ShowModal();
    }
    else if(b == CreateMediansBtn)
    {
    	unique_ptr<TCreateMediansForm> f (new TCreateMediansForm(mProject.mATIFData, this->Owner));
        f->ShowModal();
    }
    else if(b == ApplyMediansBtn)
    {
    	//unique_ptr<TCreateACQRenderStacksForm> f (new TCreateACQRenderStacksForm(mProject.mATIFData, this->Owner));
        //f->ShowModal();
    }
}

void __fastcall TATIFDataProjectFrame::RenderPythonContainersCBChange(TObject *Sender)

{
	DockerContainer* dc = (DockerContainer*) RenderPythonContainersCB->Items->Objects[RenderPythonContainersCB->ItemIndex];

    gATExplorer.mRenderPythonApps = dc;
}
//---------------------------------------------------------------------------


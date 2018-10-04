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
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TATIFDataProjectFrame *ATIFDataProjectFrame;
using namespace dsl;
using namespace at;
using namespace Poco;

static int frameNr(0);

//---------------------------------------------------------------------------
__fastcall TATIFDataProjectFrame::TATIFDataProjectFrame(ATIFDataProject& rp, TComponent* Owner)
	: TFrame(Owner),
    mProject(rp),
	mPopulateDataThread(rp.mATData)

{
    this->Name = string("ATIFDataFrame_" +  dsl::toString(frameNr++)).c_str();
    populate();
}

//---------------------------------------------------------------------------
void TATIFDataProjectFrame::populate()
{
    DataRootFolderE->setValue(mProject.getDataRootFolder());
}

//---------------------------------------------------------------------------
void __fastcall TATIFDataProjectFrame::ScanDataBtnClick(TObject *Sender)
{
    if(!mProject.mATData)
    {
        //Pretty ugly
        if(mProject.getDataRootFolder().size() && mProject.getDataRootFolder()[mProject.getDataRootFolder().size() -1] != gPathSeparator)
        {
            mProject.setDataRootFolder(mProject.getDataRootFolder() + gPathSeparator);
        }

		mProject.mATData = new ATIFData(mProject.getDataRootFolder());
    }
    mProject.mATData->reset();
	mPopulateDataThread.setData(mProject.mATData);
	mPopulateDataThread.assignCallBacks(onThreadEnter,onThreadProgress, onThreadExit);
	mPopulateDataThread.start(true);
}


void TATIFDataProjectFrame::onThreadEnter(void* arg1, void* arg2)
{
}

void TATIFDataProjectFrame::onThreadProgress(void* arg1, void* arg2)
{
    if(arg1)
    {
    	ATIFData* data = (ATIFData*) arg1;
        NrOfRibbonsLbl->Caption = IntToStr(data->getNumberOfRibbons());
        NrOfSectionsLbl->Caption = IntToStr(data->getNumberOfSections());
        NrOfTilesLbl->Caption = IntToStr(data->getNumberOfTiles());
//        NrOfSessionsLbl->Caption = IntToStr(data->getNumberOfSessions());
    }
}

void TATIFDataProjectFrame::onThreadExit(void* arg1, void* arg2)
{

}



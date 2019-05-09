#pragma hdrstop
#include "TCreateATIFDataStateTablesForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TCreateATIFDataStateTablesForm *CreateATIFDataStateTablesForm;
//---------------------------------------------------------------------------
__fastcall TCreateATIFDataStateTablesForm::TCreateATIFDataStateTablesForm(ATIFData& data, TComponent* Owner)
: TForm(Owner),
mTheData(data),
mTheThread(data)
{
    NrOfRibbonsLbl->Caption 	= IntToStr(mTheData.getNumberOfRibbons());
    NrOfSectionsLbl->Caption 	= IntToStr(mTheData.getNumberOfSections());
    NrOfTilesLbl->Caption 		= IntToStr(mTheData.getNumberOfTiles());
    NrOfSessionsLbl->Caption    = IntToStr(mTheData.getNumberOfSessions());
    NrOfChannelsLbl->Caption    = IntToStr(mTheData.getNumberOfChannels());

    int nrOfStateTables = mTheData.getNumberOfRibbons() * mTheData.getNumberOfSessions() * mTheData.getNumberOfSections();
    StateTablesLbl->Caption = IntToStr(mTheData.getNumberOfStateTables()) + " (" + IntToStr(nrOfStateTables) + ")";
}

//---------------------------------------------------------------------------
void __fastcall TCreateATIFDataStateTablesForm::RunBtnClick(TObject *Sender)
{
    if(RunBtn->Caption == "Run")
    {
    	mTheThread.assignCallBacks(onThreadEnter,onThreadProgress, onThreadExit);
	    mTheThread.start();
    }
    else
    {
        mTheThread.stop();
    }
}

void TCreateATIFDataStateTablesForm::onThreadEnter(void* arg1, void* arg2, 	void*)
{
    //Setup progress bar
    if(arg1)
    {
    	ATIFData* data = (ATIFData*) arg1;
        int nrOfStateTables = data->getNumberOfRibbons() * data->getNumberOfSessions() * data->getNumberOfSections();
        PopulatePB->Position = 0;
        PopulatePB->Max = nrOfStateTables;
    }

	RunBtn->Caption = "Stop";
	CloseBtn->Enabled = false;
}

//A way to use TThread::Synchronize with arguments
namespace CreateATIFDataStateTables
{

struct TLocalArgs
{
    ATIFData* data;
    TCreateATIFDataStateTablesForm* frame;

    void __fastcall sync()
    {
        if(!data)
        {
            return;
        }

        frame->NrOfRibbonsLbl->Caption 		= IntToStr(data->getNumberOfRibbons());
        frame->NrOfSectionsLbl->Caption 	= IntToStr(data->getNumberOfSections());
        frame->NrOfTilesLbl->Caption 		= IntToStr(data->getNumberOfTiles());
        frame->NrOfSessionsLbl->Caption     = IntToStr(data->getNumberOfSessions());
        frame->NrOfChannelsLbl->Caption     = IntToStr(data->getNumberOfChannels());
        int nrOfStateTables = data->getNumberOfRibbons() * data->getNumberOfSessions() * data->getNumberOfSections();
        int currentNumberOfStateTables = data->getNumberOfStateTables(true);
        frame->StateTablesLbl->Caption = IntToStr(currentNumberOfStateTables) + " (" + IntToStr(nrOfStateTables) + ")";
        frame->PopulatePB->Position 		= data->getNumberOfStateTables();
    }
};
}

void TCreateATIFDataStateTablesForm::onThreadProgress(void* arg1, void* arg2, void*)
{
    if(arg1)
    {
    	ATIFData* data = (ATIFData*) arg1;
        CreateATIFDataStateTables::TLocalArgs Args;
        Args.data = data;
        Args.frame = this;
        TThread::Synchronize(NULL, &Args.sync);
    }
}

void TCreateATIFDataStateTablesForm::onThreadExit(void* arg1, void* arg2, void*)
{
    if(arg1)
    {
    	ATIFData* data = (ATIFData*) arg1;

        CreateATIFDataStateTables::TLocalArgs Args;
        Args.data = data;
        Args.frame = this;
        TThread::Synchronize(NULL, &Args.sync);
    }
	RunBtn->Caption = "Run";
	CloseBtn->Enabled = true;
}

//---------------------------------------------------------------------------
//void __fastcall TCreateATIFDataStateTablesForm::DockerContainerEKeyDown(TObject *Sender,
//          WORD &Key, TShiftState Shift)
//{
//    if(Key == VK_RETURN)
//    {
//     Close();
//    }
//}



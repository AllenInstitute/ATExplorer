#include <vcl.h>
#pragma hdrstop
#include "TCreateMediansForm.h"
#include <sstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

using namespace std;
TCreateMediansForm *CreateMediansForm;
//---------------------------------------------------------------------------
__fastcall TCreateMediansForm::TCreateMediansForm(ATIFData& data, TComponent* Owner)
: TForm(Owner),
mTheData(data),
mTheThread(data)
{
    ProgressLabel->Caption = "";
    CurrentStateTbl->Caption = "";
}

//---------------------------------------------------------------------------
void __fastcall TCreateMediansForm::RunBtnClick(TObject *Sender)
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

//This is a trick to use TThread::Synchronize with arguments
struct TLocalArgs
{
    int* 		stateTable;
    string* 	msg;
    ATIFData* 	data;
    TCreateMediansForm* frame;

    void __fastcall sync()
    {
        if(!data)
        {
            return;
        }

        if(stateTable)
        {
            stringstream msgS;
            msgS << *stateTable + 1 << "(" << data->getNumberOfStateTables() << ")";
        	frame->PopulatePB->Position = *stateTable + 1;
            frame->CurrentStateTbl->Caption = msgS.str().c_str();
        }

        if(msg)
        {
            frame->ProgressLabel->Caption = string("Processing: " + (*msg)).c_str();
        }
    }
};

void TCreateMediansForm::onThreadEnter(void* arg1, void* arg2, void* arg3)
{
    //Setup progress bar
    if(arg1)
    {
    	ATIFData* data = (ATIFData*) arg1;
        PopulatePB->Position = 0;
        PopulatePB->Max = data->getNumberOfStateTables();
    }

	RunBtn->Caption = "Stop";
	CloseBtn->Enabled = false;
}

void TCreateMediansForm::onThreadProgress(void* arg1, void* arg2, void* arg3)
{
    if(arg1)
    {
        TLocalArgs Args;
        Args.data = (ATIFData*) arg1;
        Args.stateTable = (int*) arg2;
        Args.msg = (string*) arg3;
        Args.frame = this;
        TThread::Synchronize(NULL, &Args.sync);
    }
}

void TCreateMediansForm::onThreadExit(void* arg1, void* arg2, void* arg3)
{
    if(arg1)
    {
        TLocalArgs Args;
        Args.data = (ATIFData*) arg1;
        Args.stateTable = (int*) arg2;
        Args.msg = (string*) arg3;
        Args.frame = this;
        TThread::Synchronize(NULL, &Args.sync);
    }
	RunBtn->Caption = "Run";
	CloseBtn->Enabled = true;
}

void __fastcall TCreateMediansForm::FormCloseQuery(TObject *Sender, bool &CanClose)

{
//    if(mTheThread.isRunning())
//    {
//        if (MessageDlg("There are jobs running. Abort them?", mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mbCancel)
//        {
//            CanClose = false;
//        }
//        else
//        {
//			mTheThread.stop();
//        }
//    }
}



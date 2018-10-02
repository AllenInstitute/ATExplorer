#include <vcl.h>
#pragma hdrstop
#include "TParaConverterFrame.h"
#include "dslVCLUtils.h"
#include "atSSHUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "TSSHFrame"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TParaConverterFrame *ParaConverterFrame;
using namespace dsl;


//---------------------------------------------------------------------------
__fastcall TParaConverterFrame::TParaConverterFrame(TComponent* Owner)
	: TFrame(Owner)
{
   	enableDisableGroupBox(SettingsGB, false);
}

//---------------------------------------------------------------------------
void __fastcall TParaConverterFrame::TSSHFrame1ConnectBtnClick(TObject *Sender)
{
	TSSHFrame1->ConnectBtnClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TParaConverterFrame::TSSHFrame1ScSSHClientAfterConnect(TObject *Sender)
{
	TSSHFrame1->ScSSHClientAfterConnect(Sender);
   	enableDisableGroupBox(SettingsGB, true);
    this->Refresh();
}

void __fastcall TParaConverterFrame::TSSHFrame1ScSSHClientAfterDisconnect(TObject *Sender)
{
	TSSHFrame1->ScSSHClientAfterDisconnect(Sender);
   	enableDisableGroupBox(SettingsGB, false);
}


void __fastcall TParaConverterFrame::RunBtnClick(TObject *Sender)
{
	//Create remote jobs by script
    string scriptName("runner_tf.sh");

    TScSSHShell* shell = TSSHFrame1->ScSSHShell1;

    //Create an empty, runnable script on server
	string remoteScriptName = createEmptyScriptFileOnServer(shell, stdstr(OutputFolderE->Value), scriptName);
    StringList lines(getStrings(ScriptMemo));

	//Populate remote script
	if(!populateRemoteScript(shell, remoteScriptName, lines))
    {
    	Log(lError) << "Failed to populate remote script.. bailing";
    	return;
    }

    //Create command lines (jobs)
   	stringstream cmd;
    cmd << remoteScriptName <<" "
		<<stdstr(OutputFolderE->Value)<< " "
    	<<stdstr(InputFolderE->Value)<< " "
    	<<stdstr(NumberOfProcessesE->Value)<< " "
        <<NicenessE->getValue()<< " "
        <<BoxWidthE->getValue()<< " "
        <<BoxHeightE->getValue()<< " "
        <<BoxDepthE->getValue()<< " "
        <<ResolutionsE->getValue()
        << endl;


    Log(lInfo) << "Starting remote job ===========================================";
    runRemoteJob(shell, cmd.str());
}

void __fastcall TParaConverterFrame::TSSHFrame1ScSSHShell1AsyncReceive(TObject *Sender)
{
	//Parse messages from the server
    string line(stdstr(TSSHFrame1->ScSSHShell1->ReadString()));
//	if(contains("mxplutx",line))
//    {
//		Log(lInfo) << "Finished one stack...";
//    }
//    else
    {
 		Log(lDebug) << line;
    }
}

//---------------------------------------------------------------------------
void __fastcall TParaConverterFrame::KillBtnClick(TObject *Sender)
{
	;
}
//---------------------------------------------------------------------------


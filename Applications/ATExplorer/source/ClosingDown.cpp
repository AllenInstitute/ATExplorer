#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TImageForm.h"
#include "atATExplorerProject.h"
#include "ateAppUtilities.h"
//---------------------------------------------------------------------------
extern at::AppUtilities gAU;
using namespace dsl;
using namespace at;

//---------------------------------------------------------------------------
void __fastcall TMainForm::Exit1Click(TObject *Sender)
{
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;

    //Check projects for saving etc..

	Project* p  = mPTreeView.getFirst();

	if(p && p->isNeverSaved() == true)
    {
    	int mrResult = saveProject(p);
        if(mrResult == mrOk)
        {
	        mPTreeView.closeProject(p);
        }
        else if(mrResult == mrNo)
        {
            //Just close the project
            mPTreeView.closeProject(p);
        }
        else if(mrResult == mrCancel)
        {
            //Cancel shutting down
        	return;
        }
    }
    else if(p)
    {
		p->save();
        mPTreeView.closeProject(p);
    }


//	if(TSSHFrame1->isConnected())
//    {
//		TSSHFrame1->disconnect();
//	}

    Close();
}

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//    IdHTTP1->Disconnect();
	Log(lInfo) << "In FormClose";

	gAU.LogLevel.setValue(gLogger.getLogLevel());
//	if(gImageForm)
//    {
//		gImageForm->mPrepareForDeletion = true;
//    	gImageForm->Close();
//    }

	//Save project history
	gAU.BottomPanelHeight = BottomPanel->Height;
    gAU.ProjectPanelWidth = ProjectManagerPanel->Width;

//    Log(lInfo) << "CB Value: " << ConnectSSHServersOnStartupCB->getProperty()->getValue();
	gAU.GeneralProperties->write();
	gAU.ServerProperties->write();

	//Write to file
	gAU.getIniFile().save();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";


	//Check if we can close.. abort all threads..
//	if(TSSHFrame1->isConnected())
//    {
//		CanClose = false;
//    }

    if(mPTreeView.mProjectCount() > 0)
    {
		CanClose = false;
    }

	if(CanClose == false)
	{
		ShutDownTimer->Enabled = true;
	}
}


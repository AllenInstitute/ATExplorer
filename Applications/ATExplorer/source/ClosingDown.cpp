#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TImageForm.h"
#include "atATExplorerProject.h"
using namespace dsl;

//---------------------------------------------------------------------------
void __fastcall TMainForm::Exit1Click(TObject *Sender)
{
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;

    ATExplorerProject* mCurrentVCProject = mProjectManager.getCurrentProject();
	if(mCurrentVCProject && mCurrentVCProject->isNeverSaved() == true)
    {
    	int mrResult = MessageDlg("Do you want to save current project?", mtWarning, TMsgDlgButtons() << mbYes<<mbNo<<mbCancel, 0);
        if(mrResult == mrYes)
        {
    		if(closeProject() == mrCancel)
	        {
    	    	return;
        	}
        }
        else if(mrResult == mrCancel)
        {
        	return;
        }
    }
    else if(mCurrentVCProject)
    {

		mCurrentVCProject->save();
    }

    delete mCurrentVCProject;
    mCurrentVCProject = NULL;


	if(TSSHFrame1->isConnected())
    {
		TSSHFrame1->disconnect();
	}

    Close();
}

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    IdHTTP1->Disconnect();
	Log(lInfo) << "In FormClose";
	mIniFileC->clear();
	Log(lInfo) << "In main forms destructor";

	mLogLevel.setValue(gLogger.getLogLevel());
	if(gImageForm)
    {
		gImageForm->mPrepareForDeletion = true;
    	gImageForm->Close();
    }

	//Save project history
	mBottomPanelHeight = BottomPanel->Height;

	mGeneralProperties->write();
	mServer1Properties->write();
	mServer2Properties->write();

	//Write to file
	mIniFileC->save();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";

    ATExplorerProject* mCurrentVCProject = mProjectManager.getCurrentProject();
	//Check if we can close.. abort all threads..
	if(TSSHFrame1->isConnected())
    {
		CanClose = false;
    }

    else if(mCurrentVCProject && mCurrentVCProject->isNeverSaved() == false)
    {
		CanClose = false;
    }

	if(CanClose == false)
	{
		ShutDownTimer->Enabled = true;
	}
}


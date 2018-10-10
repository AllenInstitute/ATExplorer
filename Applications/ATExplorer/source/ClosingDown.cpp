#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TImageForm.h"
#include "atATExplorerProject.h"
#include "ateAppUtilities.h"
//---------------------------------------------------------------------------
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

    //Close project views
    if(mProjectObservers.count())
    {
        mProjectObservers.closeAll();
    }

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


    Close();
}

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "In FormClose";

	gAU.LogLevel.setValue(gLogger.getLogLevel());

	//Save project history
	gAU.BottomPanelHeight = BottomPanel->Height;
    gAU.ProjectPanelWidth = ProjectManagerPanel->Width;

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

    if(mProjectObservers.count())
    {
		CanClose = false;
    }
    else if(mPTreeView.mProjectCount() > 0)
    {
		CanClose = false;
    }

	if(CanClose == false)
	{
		ShutDownTimer->Enabled = true;
	}
}


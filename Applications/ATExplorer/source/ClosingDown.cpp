#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TImageForm.h"
#include "atATExplorerProject.h"
#include "ATExplorerUIProperties.h"
#include "atATExplorer.h"
//---------------------------------------------------------------------------
using namespace dsl;
using namespace at;

extern ATExplorer gATExplorer;
extern ATExplorerUIProperties gUIProperties;
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
    if(mTreeItemObservers.count())
    {
        mTreeItemObservers.closeAll();
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

	gATExplorer.Properties.LogLevel.setValue(gLogger.getLogLevel());

	//Save project history
	gUIProperties.BottomPanelHeight = BottomPanel->Height;
    gUIProperties.ProjectPanelWidth = ProjectManagerPanel->Width;

	gUIProperties.GeneralProperties->write();
    gATExplorer.writeProperties();

	//Write to file
	gUIProperties.getIniFile().save();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";
	//Check if we can close.. abort all threads..

    if(mTreeItemObservers.count())
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


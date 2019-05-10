#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "ATExplorerUIProperties.h"
#include "dslVCLUtils.h"
#include "atATExplorer.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------
using namespace dsl;
using namespace at;

extern ATExplorerUIProperties gUIProperties;
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    static bool firstShow(true);

    if(mIsStyleMenuPopulated == false)
    {
        populateStyleMenu(ThemesMenu, ThemesMenuClick);
        mIsStyleMenuPopulated = true;
	}

    if(gUIProperties.LastOpenedProject.getValue().size() > 0 && firstShow == true)
    {
        string projectFile(gUIProperties.LastOpenedProject.getValue());

        if(fileExists(projectFile))
        {
        	FileOpen1Accept(NULL);
        }
        else
        {
            MessageDlg("The File could not be found", mtWarning, TMsgDlgButtons() << mbOK, 0);
			gUIProperties.LastOpenedProject.setValue("");
        }
    }
    firstShow = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	this->Caption = vclstr(createWindowTitle("ATExplorer", Application));
    this->DoubleBuffered = true;
    LogMemoFrame1->init();
}


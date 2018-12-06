#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "ATExplorerUIProperties.h"
#include "dslVCLUtils.h"
#include "atATExplorer.h"
//---------------------------------------------------------------------------
using namespace dsl;
using namespace at;

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    static bool firstShow(true);

    if(mIsStyleMenuPopulated == false)
    {
        populateStyleMenu(ThemesMenu, ThemesMenuClick);
        mIsStyleMenuPopulated = true;
	}

    if(gAU.LastOpenedProject.getValue().size() > 0 && firstShow == true)
    {
        FileOpen1Accept(NULL);
    }
    firstShow = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	this->Caption = vclstr(createWindowTitle("ATExplorer", Application));
    this->DoubleBuffered = true;
    TLogMemoFrame1->init();
}


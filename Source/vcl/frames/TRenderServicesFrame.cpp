#include <vcl.h>
#pragma hdrstop
#include "TRenderServicesFrame.h"
#include "dslVCLUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TRenderServicesFrame *RenderServicesFrame;

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TRenderServicesFrame::TRenderServicesFrame(TComponent* Owner)
	:
    TFrame(Owner)
    {}

//---------------------------------------------------------------------------
bool TRenderServicesFrame::populate(Properties& props)
{
    //Assign external properties with UI properties
    props.disableEdits();


    if(props.getProperty("LOCAL_CACHE_FOLDER"))
    {

    }

    props.enableEdits();
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TRenderServicesFrame::TestRenderServiceBtnClick(TObject *Sender)
{
    //Get some render owners
    MessageDlg("Not Implemented yet", mtInformation, TMsgDlgButtons() << mbOK, 0);
}


void __fastcall TRenderServicesFrame::AddRenderServiceBtnClick(TObject *Sender)
{
    ;
}
//---------------------------------------------------------------------------


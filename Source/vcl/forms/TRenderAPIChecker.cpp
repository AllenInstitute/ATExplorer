#pragma hdrstop
#include "TRenderAPIChecker.h"
#include "atRenderProject.h"
#include "atRenderClient.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TRenderAPIChecker *RenderAPIChecker;


using namespace at;
using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TRenderAPIChecker::TRenderAPIChecker(RenderServiceParameters& rsp, TComponent* Owner)
	: TForm(Owner),
    mHost(rsp)
{}

//---------------------------------------------------------------------------
void __fastcall TRenderAPIChecker::RequestBtnClick(TObject *Sender)
{
    //Get some render owners
    RenderProject dummyProject("Dummy", &mHost);
    RenderClient   mRC(dummyProject, IdHTTP1, &mHost);
	ResponseMemo->Clear();
	StringList response;

    if(APIs->ItemIndex == 0)
    {
        //Get server properties
	    response = mRC.getServerProperties();
    }
    else if(APIs->ItemIndex == 1)
    {
	    response = mRC.getOwners();
    }

    RequestURL->setValue(mRC.getLastRequestURL());
    //Populate memo with response
    for(int i = 0; i < response.count(); i++)
    {
		ResponseMemo->Lines->Add(vclstr(response[i]));
    }
}

//---------------------------------------------------------------------------
void __fastcall TRenderAPIChecker::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}


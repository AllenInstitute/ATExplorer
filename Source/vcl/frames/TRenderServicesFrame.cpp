#include <vcl.h>
#pragma hdrstop
#include "TRenderServicesFrame.h"
#include "dslVCLUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include "atRenderServiceParameters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TRenderServicesFrame *RenderServicesFrame;

using namespace dsl;
using namespace at;
//---------------------------------------------------------------------------
__fastcall TRenderServicesFrame::TRenderServicesFrame(ATExplorer& e, TComponent* Owner)
	:
    TFrame(Owner),
    mExplorer(e)
    {}

//---------------------------------------------------------------------------
bool TRenderServicesFrame::populate()
{
    //Assign external properties with UI properties
    ServicesLB->Clear();

    RenderServiceParameters* rsp = mExplorer.getFirstRenderService();
    while(rsp)
    {
		ServicesLB->AddItem(rsp->getName().c_str(), NULL);
        rsp = mExplorer.getNextRenderService();
    }

    if(ServicesLB->Items->Count)
    {
        ServicesLB->ItemIndex = 0;
		ServicesLB->OnClick(NULL);
    }


    return true;
}

//---------------------------------------------------------------------------
void __fastcall TRenderServicesFrame::TestRenderServiceBtnClick(TObject *Sender)
{
    //Get some render owners
    MessageDlg("Not Implemented yet", mtInformation, TMsgDlgButtons() << mbOK, 0);
}

//---------------------------------------------------------------------------
void __fastcall TRenderServicesFrame::AddRenderServiceBtnClick(TObject *Sender)
{
    ;
}

//---------------------------------------------------------------------------
void __fastcall TRenderServicesFrame::ServicesLBClick(TObject *Sender)
{
    if(ServicesLB->ItemIndex == -1)
    {
        return;
    }

    string serviceName = stdstr(ServicesLB->Items->Strings[ServicesLB->ItemIndex]);

    //Get the service that was clicked on
    RenderServiceParameters* s = mExplorer.getRenderService(serviceName);
    PropertiesSP p = s->getProperties();
    if(p && p->getProperty("HOST"))
    {
        HostE->assignExternalProperty(dynamic_cast<Property<string>* >(p->getProperty("HOST")));
        HostE->Enabled =  p->getProperty("HOST")->isInEditMode();

    }
}



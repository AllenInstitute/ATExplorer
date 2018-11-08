#include <vcl.h>
#pragma hdrstop
#include "TRenderServicesFrame.h"
#include "dslVCLUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include "atRenderServiceParameters.h"
#include "TSimpleTextInputDialog.h"
#include <memory>
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
using namespace std;
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

//    if(ServicesLB->Items->Count)
//    {
//        ServicesLB->ItemIndex = 0;
//		ServicesLB->OnClick(NULL);
//    }

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
	unique_ptr<TNewValueE> newValue(new TNewValueE(this));

	newValue->Caption = "New RenderService name";
	newValue->NewValueE->EditLabel->Caption = "Give the service a name";
    newValue->setText("New Service");

    while(newValue->ShowModal() == mrOk)
    {
        if(mExplorer.getRenderService(newValue->getText()))
        {
            if(MessageDlg("A service with that name already exists.. Try again?", mtConfirmation, TMsgDlgButtons() << mbYes<<mbNo, 0) == mrYes)
            {
                continue;
            }
            else
            {
            	break;
            }
        }
        else
        {
	    	RenderServiceParameters* rsp = mExplorer.createRenderService(newValue->getText());
	    	populate();

            mNewServices.append(rsp->mProperties);

            //Select the last one
            if(ServicesLB->Items->Count)
            {
                ServicesLB->ItemIndex = ServicesLB->Items->Count - 1;
                ServicesLB->OnClick(NULL);
            }

            break;
        }
    }
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

    if(!s)
    {
        Log(lError) << "There was a problem with service: " << serviceName;
    	return;
    }

    PropertiesSP props = s->getProperties();
    if(props && props->getProperty("PROTOCOL"))
    {
        ProtocolE->assignExternalProperty(dynamic_cast<Property<string>* >(props->getProperty("PROTOCOL")));
        ProtocolE->Enabled =  props->getProperty("PROTOCOL")->isInEditMode();
    }

    if(props && props->getProperty("HOST"))
    {
        HostE->assignExternalProperty(dynamic_cast<Property<string>* >(props->getProperty("HOST")));
        HostE->Enabled =  props->getProperty("HOST")->isInEditMode();
        ProtocolE->update();
    }

    if(props && props->getProperty("PORT"))
    {
        PortE->assignExternalProperty(dynamic_cast<Property<int>* >(props->getProperty("PORT")));
        PortE->Enabled =  props->getProperty("PORT")->isInEditMode();
    }

    if(props && props->getProperty("VERSION"))
    {
        VersionE->assignExternalProperty(dynamic_cast<Property<string>* >(props->getProperty("VERSION")));
        VersionE->Enabled =  props->getProperty("VERSION")->isInEditMode();
    }

    if(props && props->getProperty("MAX_TILES_TO_RENDER"))
    {
        MaxTileSpecsToRenderE->assignExternalProperty(dynamic_cast<Property<int>* >(props->getProperty("MAX_TILES_TO_RENDER")));
        MaxTileSpecsToRenderE->Enabled =  props->getProperty("MAX_TILES_TO_RENDER")->isInEditMode();
    }
}

//---------------------------------------------------------------------------
void __fastcall TRenderServicesFrame::RenameClick(TObject *Sender)
{
    if(ServicesLB->ItemIndex == -1)
    {
        return;
    }

	unique_ptr<TNewValueE> newValue(new TNewValueE(this));
    string serviceName = stdstr(ServicesLB->Items->Strings[ServicesLB->ItemIndex]);
    newValue->setText(serviceName);

    if(newValue->ShowModal() == mrOk)
    {
        //Change value
	    //Get the service that was clicked on
    	RenderServiceParameters* s = mExplorer.getRenderService(serviceName);
        s->setName(newValue->getText());
		ServicesLB->Items->Strings[ServicesLB->ItemIndex] = newValue->getText().c_str();
    }
}

void __fastcall TRenderServicesFrame::RemoveServiceBtnClick(TObject *Sender)
{
    if(ServicesLB->ItemIndex == -1)
    {
        return;
    }

    string serviceName = stdstr(ServicesLB->Items->Strings[ServicesLB->ItemIndex]);
    mExplorer.removeRenderService(serviceName);
    ServicesLB->DeleteSelected();
}

bool TRenderServicesFrame::applyEditsForNewServices()
{
	mNewServices.applyEdits();
}



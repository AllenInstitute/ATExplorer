#include <vcl.h>
#pragma hdrstop
#include "TDockerContainersFrame.h"
#include "dslVCLUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include "atDockerContainer.h"
#include "TSimpleTextInputDialog.h"
#include <memory>
#include "atRenderClient.h"
#include "TRenderAPIChecker.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TDockerContainersFrame *DockerContainersFrame;

using namespace dsl;
using namespace at;
using namespace std;
//---------------------------------------------------------------------------
__fastcall TDockerContainersFrame::TDockerContainersFrame(ATExplorer& e, TComponent* Owner)
	:
    TFrame(Owner),
    mExplorer(e)
    {}

//---------------------------------------------------------------------------
bool TDockerContainersFrame::populate()
{
    //Assign external properties with UI properties
    ItemsLB->Clear();

    DockerContainer* rsp = mExplorer.getFirstDockerContainer();
    while(rsp)
    {
		ItemsLB->AddItem(rsp->getName().c_str(), NULL);
        rsp = mExplorer.getNextDockerContainer();
    }

//    if(ItemsLB->Items->Count)
//    {
//        ItemsLB->ItemIndex = 0;
//		ItemsLB->OnClick(NULL);
//    }

    return true;
}

DockerContainer* TDockerContainersFrame::getCurrent()
{
    string serviceName = stdstr(ItemsLB->Items->Strings[ItemsLB->ItemIndex]);

    //Get the service that was clicked on
    return mExplorer.getDockerContainer(serviceName);
}

//---------------------------------------------------------------------------
void __fastcall TDockerContainersFrame::TestBtnClick(TObject *Sender)
{
//    //Get the currently selected service
//    DockerContainer rsp("test", HostE->getValue(), PortE->getValue(), VersionE->getValue());
//    unique_ptr<TRenderAPIChecker> f(new TRenderAPIChecker(rsp, this));
//
//    f->Caption = vclstr("Testing HOST: " + HostE->getValue());
//    f->ShowModal();
}

//---------------------------------------------------------------------------
void __fastcall TDockerContainersFrame::AddBtnClick(TObject *Sender)
{
	unique_ptr<TNewValueE> newValue(new TNewValueE(this));

	newValue->Caption = "New Docker Container Name";
	newValue->NewValueE->EditLabel->Caption = "Give the Docker Container a name";
    newValue->setText("New Container");

    while(newValue->ShowModal() == mrOk)
    {
        if(mExplorer.getDockerContainer(newValue->getText()))
        {
            if(MessageDlg("A Container with that name already exists.. Try again?", mtConfirmation, TMsgDlgButtons() << mbYes<<mbNo, 0) == mrYes)
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
	    	DockerContainer* item = mExplorer.createDockerContainer(newValue->getText());
	    	populate();

            mNewContainers.append(item->mProperties);

            //Select the last one
            if(ItemsLB->Items->Count)
            {
                ItemsLB->ItemIndex = ItemsLB->Items->Count - 1;
                ItemsLB->OnClick(NULL);
            }

            break;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TDockerContainersFrame::ItemsLBClick(TObject *Sender)
{
    if(ItemsLB->ItemIndex == -1)
    {
        return;
    }

    string serviceName = stdstr(ItemsLB->Items->Strings[ItemsLB->ItemIndex]);

    //Get the service that was clicked on
    DockerContainer* s = mExplorer.getDockerContainer(serviceName);

    if(!s)
    {
        Log(lError) << "There was a problem with service: " << serviceName;
    	return;
    }

    PropertiesSP props = s->getProperties();
//    if(props && props->getProperty("NAME"))
//    {
//        ContainerNameE->assignExternalProperty(dynamic_cast<Property<string>* >(props->getProperty("NAME")));
//        ContainerNameE->Enabled =  props->getProperty("NAME")->isInEditMode();
//    }
}

//---------------------------------------------------------------------------
void __fastcall TDockerContainersFrame::RenameClick(TObject *Sender)
{
    if(ItemsLB->ItemIndex == -1)
    {
        return;
    }

	unique_ptr<TNewValueE> newValue(new TNewValueE(this));
    string serviceName = stdstr(ItemsLB->Items->Strings[ItemsLB->ItemIndex]);
    newValue->setText(serviceName);

    if(newValue->ShowModal() == mrOk)
    {
        //Change value
	    //Get the service that was clicked on
    	DockerContainer* s = mExplorer.getDockerContainer(serviceName);
        s->setName(newValue->getText());
		ItemsLB->Items->Strings[ItemsLB->ItemIndex] = newValue->getText().c_str();
    }
}

void __fastcall TDockerContainersFrame::RemoveBtnClick(TObject *Sender)
{
    if(ItemsLB->ItemIndex == -1)
    {
        return;
    }

    string serviceName = stdstr(ItemsLB->Items->Strings[ItemsLB->ItemIndex]);
    mExplorer.removeDockerContainer(serviceName);
    ItemsLB->DeleteSelected();
}

bool TDockerContainersFrame::applyEditsForNewServices()
{
	mNewContainers.applyEdits();
    return true;
}



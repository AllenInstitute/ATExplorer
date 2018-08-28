#include <vcl.h>
#pragma hdrstop
#include "TRenderProjectFrame.h"
#include "dslVCLUtils.h"
#include "atRenderServiceParameters.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TRenderProjectFrame *RenderProjectFrame;

using namespace dsl;
using namespace at;
int frameNr(0);
//---------------------------------------------------------------------------
__fastcall TRenderProjectFrame::TRenderProjectFrame(RenderProject* rp, TComponent* Owner)
	: TFrame(Owner),
    mRP(rp),
    mRC(IdHTTP1)
{
	mRC.setBaseURL(mHostURL);

    this->Name = string("RPFrame_" +  dsl::toString(frameNr++)).c_str();
    populate();
}

void TRenderProjectFrame::populate()
{
    OwnerLabel->Caption 	= vclstr(mRP->getProjectOwner());
    ProjectLabel->Caption 	= vclstr(mRP->getRenderProjectName());

    RenderServiceParameters rsp(mRP->getRenderServiceParameters());
	mRC.setBaseURL(rsp.getBaseURL());

    //Get stacks for project
    StringList stacks = mRC.getStacksForProject(mRP->getProjectOwner(), mRP->getRenderProjectName());
    if(stacks.size())
    {
		StackCB->ItemIndex = populateDropDown(stacks, 		StackCB);
//		populateCheckListBox(stacks, 	StacksForProjectCB);
    }
	StackCBChange(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TRenderProjectFrame::StackCBChange(TObject *Sender)
{
    if(StackCB->ItemIndex == -1)
    {
		return;
    }

//    string stack = stdstr(StackCB->Items->Strings[StackCB->ItemIndex]);
//	gAU.CurrentStack.setValue(stack);
//	mRC.getProject().init(gAU.CurrentOwner.getValue(), gAU.CurrentProject.getValue(), gAU.CurrentStack.getValue());
//
   	getValidZsForStack();
//
//	ClickZ(NULL);
//    updateROIs();
//    //Update stack generation page
//	//User changed stack.. Clear check list box and select current one
//    for(int i = 0; i < StacksForProjectCB->Items->Count; i++)
//    {
//    	StacksForProjectCB->Checked[i] = (StacksForProjectCB->Items->Strings[i] == StackCB->Text) ? true : false;
//    }
//
//	StackCB->Hint = vclstr(stack);
//
//    //Disable uninitialized sections of the UI
//	enableDisableGroupBox(imageParasGB, true);
//	enableDisableGroupBox(Zs_GB, true);
//	mRenderEnabled = true;
}

void __fastcall TRenderProjectFrame::getValidZsForStack()
{
	//Fetch valid zs for current project

    mRC.init(mRP->getProjectOwner(), mRP->getRenderProjectName(), stdstr(StackCB->Text));

    StringList zs = mRC.getValidZs();

	Log(lInfo) << "Fetched "<<zs.count()<<" valid z's";

	Zs_GB->Caption = " Z Values (" + IntToStr((int) zs.count()) + ") ";

    //Populate list box
	populateCheckListBox(zs, mZs);
    mZs->CheckAll(cbChecked);
}




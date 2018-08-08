#include <vcl.h>
#pragma hdrstop
#include "TAffineTransformationFrame.h"
#include <sstream>
#include "dslStringUtils.h"
#include "dslLogger.h"
#include "dslMathUtils.h"
#include "dslVCLUtils.h"
#include "atVolumeCreatorMessages.h"
//-----------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TRenderPythonRemoteScriptFrame"
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTIntLabel"
#pragma resource "*.dfm"
TAffineTransformationFrame *AffineTransformationFrame;

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TAffineTransformationFrame::TAffineTransformationFrame(TComponent* Owner)
	: TRenderPythonRemoteScriptFrame("renderapps.stack.apply_global_affine_to_stack", Owner)
{}

void __fastcall TAffineTransformationFrame::onSSHData(const string& data)
{
    StringList lines(data, '\n');
    for(int i = 0; i < lines.count(); i++)
    {
    	Log(lDebug5) << "SSH data: " << lines[i];
    }

    for(int i = 0; i < lines.count(); i++)
    {
        string dataStr = lines[i];
        if(contains("generateStackDataForZ: exit", dataStr))
        {
            int sectionNr = toInt(dataStr, false);
            ProgressBar1->Position = sectionNr;
            Log(lInfo) << "Finished section: " << sectionNr;
            ZLbl->setValue(ProgressBar1->Position);
        }
        else if (contains("processing completed", dataStr))
        {
            Log(lInfo) << "Processing completed";
            //Send message to application that Affine processing completed, and do what needs to be done
            SendTextMessage(Application->MainForm->Handle,  FINISHED_RENDER_ROTATE, 0, "Finished");
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TAffineTransformationFrame::ExecuteBtnClick(TObject *Sender)
{
    //Create command string for current UI parameters
    StringList stacks = getCheckedItems(StacksForProjectCB);
    if(!stacks.count())
    {
        Log(lError) << "You must select at least one stack to transform";
        return;
    }

    stringstream cmd;
    mScripter.setRemoteCommand("docker exec renderapps_develop python -m");
    mScripter.clearArguments();

    mScripter.addArgument("--render.host " 		        + RenderHostE->getValue());
	mScripter.addArgument("--render.port " 		        + dsl::toString(RenderHostPortE->getValue()));
	mScripter.addArgument("--render.owner " 	        + RenderOwnerE->getValue());
	mScripter.addArgument("--render.project " 	        + RenderProjectE->getValue());
	mScripter.addArgument("--render.client_scripts " 	+ RenderClientScriptsFolderE->getValue());

//    stringstream stacksArg;
//    stacksArg << "[";
//
//
//    for(int i = 0; i < stacks.count(); i++)
//    {
//        stacksArg << "\"" << stacks[i] << "\"";
//        if(i < stacks.count() - 1)
//        {
//            stacksArg << ",";
//        }
//    }
//
//    stacksArg << "]";

//	mScripter.addArgument("--input_stacks " 				+ stacksArg.str());
	mScripter.addArgument("--input_stack " 				+ stacks[0]);

    if(AppendToCurrentStackCB->Checked)
    {
   		mScripter.addArgument("--output_stack " 	   	+ stacks[0]);
    }
    else
    {
		mScripter.addArgument("--output_stack " 	   	+ stacks[0] + "_AFF");
    }

    string dateTime(getFormattedDateTimeString("Affine_%Y_%b_%d_%R:%S"));
	mScripter.addArgument("--transformId " 				+ dateTime);
	mScripter.addArgument("--pool_size " 				+ dsl::toString(stacks.count()));

    //Setup rotation matrix
    double theta(toRadians(RotationE->getValue()));
    double r1 = cos(theta);
	double r2 = sin(theta) * -1.0;
	double r3 = sin(theta);
	double r4 = cos(theta);

	mScripter.addArgument("--M00 " 						+ dsl::toString(r1));
	mScripter.addArgument("--M01 " 						+ dsl::toString(r2));
	mScripter.addArgument("--M10 " 						+ dsl::toString(r3));
	mScripter.addArgument("--M11 " 						+ dsl::toString(r4));

    double t1 = TranslateXE->getValue();
	double t2 = TranslateYE->getValue();

    double b0 = r1*t1 + r2*t2;
    double b1 = r3*t1 + r4*t2;

	mScripter.addArgument("--B0 " 						+ dsl::toString(b0));
	mScripter.addArgument("--B1 " 						+ dsl::toString(b1));

    cmd << mScripter.createFullRemoteCommand() << endl;
    Log(lInfo) << "Remote command: " << cmd.str();

	ZLbl->setValue(0);
    ProgressBar1->Min = 0;

    ProgressBar1->Max = mRC.getValidZs().size() - 1;
    ProgressBar1->Position = 0;
    mScripter.run();
}

//---------------------------------------------------------------------------
void __fastcall TAffineTransformationFrame::DeleteStackAExecute(TObject *Sender)
{

	if(StacksForProjectCB->ItemIndex != -1)
    {
	    //Just append _hidden to stack name
	    string currentStackName(stdstr(StacksForProjectCB->Items->Strings[StacksForProjectCB->ItemIndex]));
        Log(lInfo) << "Deleting stack: " << currentStackName;
	    string newStackName("HIDDEN_" + currentStackName);
	    mRC.renameStack(currentStackName, newStackName);
    }
    else
    {
        Log(lWarning) << "No stack is selected";
    }
}

//---------------------------------------------------------------------------
void __fastcall TAffineTransformationFrame::StacksPopupPopup(TObject *Sender)

{
    //Figure wich item was clicked
    //Only opup if an item is selected

}



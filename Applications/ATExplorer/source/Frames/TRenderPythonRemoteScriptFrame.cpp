#include <vcl.h>
#pragma hdrstop
#include "TRenderPythonRemoteScriptFrame.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TRenderPythonRemoteScriptFrame *RenderPythonRemoteScriptFrame;

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TRenderPythonRemoteScriptFrame::TRenderPythonRemoteScriptFrame(const string& scriptName, TComponent* Owner)
	: TFrame(Owner),
    mScripter(scriptName),
    mRC(NULL)
{
}

//---------------------------------------------------------------------------
void TRenderPythonRemoteScriptFrame::populate(RenderClient& rc, TScSSHShell* shell)
{
    try
    {
        Log(lInfo) << "Populating frame";
		mScripter.useConnection(shell);

        mRC.assignConnection(rc.getConnection());
        mRC.setBaseURL(rc.getBaseURL());

        RenderProject p = rc.getCurrentProject();
        RenderOwnerE->setValue(p.mOwner);
        RenderProjectE->setValue(p.mProject);
        mRC.setRenderProject(rc.getRenderProject());

        //Populate stacks
        StringList s = mRC.getStacksForProject(p.mOwner, p.mProject);
        if(s.size())
        {
            populateCheckListBox(s, StacksForProjectCB);
        }

        //Check current one
        for(int i = 0; i < StacksForProjectCB->Items->Count; i++)
        {

            if(StacksForProjectCB->Items->Strings[i] == vclstr(p.mStack))
            {
                StacksForProjectCB->Checked[i] = true;
            }
            else
            {
                StacksForProjectCB->Checked[i] = false;
            }
        }
    }
    catch(...)
    {
        Log(lError) << "Bad stuff..";
    }
}



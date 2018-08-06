#ifndef TRenderPythonRemoteScriptFrameH
#define TRenderPythonRemoteScriptFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "atRemoteScripter.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.CheckLst.hpp>
#include "atRenderClient.h"
//---------------------------------------------------------------------------
using at::RemoteScripter;


class PACKAGE TRenderPythonRemoteScriptFrame : public TFrame
{
    __published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TSTDStringLabeledEdit *RenderHostE;
	TSTDStringLabeledEdit *RenderOwnerE;
	TSTDStringLabeledEdit *RenderProjectE;
	TSTDStringLabeledEdit *RenderClientScriptsFolderE;
	TIntegerLabeledEdit *RenderHostPortE;
	TButton *ExecuteBtn;
	TPanel *Panel2;
	TCheckListBox *StacksForProjectCB;
	TGroupBox *StacksGB;
	TGroupBox *GroupBox2;

    protected:
        RemoteScripter          mScripter;
        RenderClient            mRC;

    public:
        			__fastcall  TRenderPythonRemoteScriptFrame(const string& scriptName, TComponent* Owner);
        virtual void            populate(RenderClient& client, TScSSHShell* shell);
};

extern PACKAGE TRenderPythonRemoteScriptFrame *RenderPythonRemoteScriptFrame;
#endif

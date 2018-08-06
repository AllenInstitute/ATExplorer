#ifndef TParaConverterFrameH
#define TParaConverterFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerLabeledEdit.h"
#include "TSSHFrame.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslTSTDStringLabeledEdit.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class PACKAGE TParaConverterFrame : public TFrame
{
    __published:	// IDE-managed Components
	TGroupBox *SettingsGB;
        TIntegerLabeledEdit *NumberOfProcessesE;
        TIntegerLabeledEdit *BoxHeightE;
        TIntegerLabeledEdit *BoxWidthE;
        TIntegerLabeledEdit *BoxDepthE;
        TGroupBox *GroupBox2;
        TSTDStringLabeledEdit *InputFolderE;
        TGroupBox *GroupBox3;
        TSTDStringLabeledEdit *OutputFolderE;
        TGroupBox *RunGB;
	TButton *RunBtn;
	TSSHFrame *TSSHFrame1;
	TMemo *ScriptMemo;
	TIntegerLabeledEdit *NicenessE;
	TPanel *Panel1;
	TSTDStringLabeledEdit *ResolutionsE;
	TButton *KillBtn;
        void __fastcall TSSHFrame1ConnectBtnClick(TObject *Sender);
	void __fastcall TSSHFrame1ScSSHClientAfterConnect(TObject *Sender);
	void __fastcall TSSHFrame1ScSSHClientAfterDisconnect(TObject *Sender);
	void __fastcall RunBtnClick(TObject *Sender);
	void __fastcall TSSHFrame1ScSSHShell1AsyncReceive(TObject *Sender);
	void __fastcall KillBtnClick(TObject *Sender);

    private:

    public:
                            __fastcall TParaConverterFrame(TComponent* Owner);

};

extern PACKAGE TParaConverterFrame *ParaConverterFrame;
#endif

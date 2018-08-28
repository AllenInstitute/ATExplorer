#ifndef TSelectRenderProjectParametersFormH
#define TSelectRenderProjectParametersFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "atRenderClient.h"
//---------------------------------------------------------------------------

using at::RenderClient;

class TSelectRenderProjectParametersForm : public TForm
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
	TSTDStringLabeledEdit *BaseURLE;
	TIntegerLabeledEdit *HostPort;
        TGroupBox *GroupBox2;
        TComboBox *ProjectCB;
        TComboBox *OwnerCB;
        TLabel *Label1;
        TLabel *Label2;
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
        TIdHTTP *IdHTTP1;
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall OwnerCBChange(TObject *Sender);
    private:
        RenderClient                    mRC;

    public:
        					__fastcall 	TSelectRenderProjectParametersForm(TComponent* Owner);
        string                          getRenderOwner();
        string                          getRenderProject();
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectRenderProjectParametersForm *SelectRenderProjectParametersForm;
//---------------------------------------------------------------------------
#endif

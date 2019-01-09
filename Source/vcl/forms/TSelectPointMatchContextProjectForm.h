#ifndef TSelectPointMatchContextProjectFormH
#define TSelectPointMatchContextProjectFormH
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
#include "atRenderServiceParameters.h"
#include "atATExplorer.h"
#include "atPointMatchContext.h"

//---------------------------------------------------------------------------
using at::RenderClient;
using at::RenderServiceParameters;
using at::RenderProject;
using at::ATExplorer;
using at::PointMatchContext;
//---------------------------------------------------------------------------
class PACKAGE TSelectPointmatchContextProjectForm : public TForm
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
	TComboBox *CollectionCB;
        TComboBox *OwnerCB;
        TLabel *Label1;
        TLabel *Label2;
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
        TIdHTTP *IdHTTP1;
		TButton *PopulateOwnersBtn;
		TComboBox *RenderServicesCB;
		void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
		void __fastcall OwnerCBChange(TObject *Sender);
		void __fastcall PopulateOwnersBtnClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall RenderServicesCBCloseUp(TObject *Sender);
        void __fastcall RenderServicesCBChange(TObject *Sender);

    private:
        RenderProject                   mRP;
        RenderClient                    mRC;
        ATExplorer&                     mExplorer;

    public:
        					__fastcall 	TSelectPointmatchContextProjectForm(ATExplorer& e, TComponent* Owner);
        string                          getRenderOwner();
        PointMatchContext*              getPointMatchContext();
        RenderServiceParameters*        getRenderService();
};

extern PACKAGE TSelectPointmatchContextProjectForm *SelectPointmatchContextProjectForm;

#endif

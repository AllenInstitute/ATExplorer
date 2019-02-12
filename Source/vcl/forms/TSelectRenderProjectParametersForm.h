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
#include "atRenderServiceParameters.h"
#include "atATExplorer.h"

//---------------------------------------------------------------------------

using at::RenderClient;
using at::RenderServiceParameters;
using at::RenderProject;
using at::ATExplorer;
//---------------------------------------------------------------------------
class PACKAGE TSelectRenderProjectParametersForm : public TForm
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TComboBox *ProjectCB;
        TComboBox *OwnerCB;
        TLabel *Label1;
        TLabel *Label2;
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
		TButton *PopulateOwnersBtn;
		TGroupBox *GroupBox3;
		TSTDStringLabeledEdit *OutputDataRootFolderE;
		TButton *BrowseForDataOutputPathBtn;
		TComboBox *RenderServicesCB;
		void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
		void __fastcall OwnerCBChange(TObject *Sender);
		void __fastcall PopulateOwnersBtnClick(TObject *Sender);
        void __fastcall BrowseForDataOutputPathBtnClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall RenderServicesCBCloseUp(TObject *Sender);
        void __fastcall RenderServicesCBChange(TObject *Sender);

    private:
        RenderProject                   mRP;
        RenderClient                    mRC;
        ATExplorer&                     mExplorer;

    public:
        					__fastcall 	TSelectRenderProjectParametersForm(ATExplorer& e, TComponent* Owner);
        string                          getRenderOwner();
        string                          getRenderProject();
        RenderServiceParameters*        getRenderService();
        string                          getOutputFolderLocation();
};

extern PACKAGE TSelectRenderProjectParametersForm *SelectRenderProjectParametersForm;

#endif

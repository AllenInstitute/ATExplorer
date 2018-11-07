#ifndef TRenderServicesFrameH
#define TRenderServicesFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerLabeledEdit.h"
#include "dslTPropertyCheckBox.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslProperties.h"
#include "atATExplorer.h"
//---------------------------------------------------------------------------

using dsl::Properties;
using at::ATExplorer;

//---------------------------------------------------------------------------
class PACKAGE TRenderServicesFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox4;
	TSTDStringLabeledEdit *HostE;
        TButton *TestRenderServiceBtn;
        TIntegerLabeledEdit *maxTileSpecsToRenderE;
        TIntegerLabeledEdit *RenderPort;
	TListBox *ServicesLB;
	TPanel *Panel1;
	TButton *AddRenderServiceBtn;
	TButton *RemoveServiceBtn;

	void __fastcall TestRenderServiceBtnClick(TObject *Sender);
	void __fastcall AddRenderServiceBtnClick(TObject *Sender);
	void __fastcall ServicesLBClick(TObject *Sender);

    private:
		ATExplorer& 			mExplorer;

    public:
        			__fastcall 	TRenderServicesFrame(ATExplorer& e, TComponent* Owner);
        bool                	populate();

};

extern PACKAGE TRenderServicesFrame *RenderServicesFrame;
#endif

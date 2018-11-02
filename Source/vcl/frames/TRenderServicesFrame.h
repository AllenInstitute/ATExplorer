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

using dsl::Properties;
//---------------------------------------------------------------------------
class PACKAGE TRenderServicesFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox4;
        TSTDStringLabeledEdit *BaseURLE;
        TButton *TestRenderServiceBtn;
        TIntegerLabeledEdit *maxTileSpecsToRenderE;
        TIntegerLabeledEdit *RenderPort;
	TListBox *ServicesLB;
	TPanel *Panel1;
	TButton *AddRenderServiceBtn;
	TButton *RemoveServiceBtn;

	void __fastcall TestRenderServiceBtnClick(TObject *Sender);
	void __fastcall AddRenderServiceBtnClick(TObject *Sender);

    private:

    public:
        			__fastcall 	TRenderServicesFrame(TComponent* Owner);
        bool                	populate(Properties& props);
};

extern PACKAGE TRenderServicesFrame *RenderServicesFrame;
#endif

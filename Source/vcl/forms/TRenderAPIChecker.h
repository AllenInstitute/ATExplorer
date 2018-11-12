#ifndef TRenderAPICheckerH
#define TRenderAPICheckerH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "atRenderServiceParameters.h"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "dslTSTDStringLabeledEdit.h"
//---------------------------------------------------------------------------


using at::RenderServiceParameters;
//---------------------------------------------------------------------------
class PACKAGE TRenderAPIChecker : public TForm
{
    __published:
        TRadioGroup *APIs;
	TMemo *ResponseMemo;
	TPanel *Panel1;
	TButton *RequestBtn;
	TGroupBox *GroupBox1;
	TIdHTTP *IdHTTP1;
	TPanel *Panel2;
	TButton *CloseBtn;
	TGroupBox *GroupBox2;
	TPanel *Panel3;
	TSTDStringLabeledEdit *RequestURL;
	void __fastcall RequestBtnClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

    private:
    	RenderServiceParameters&            mHost;

    public:
        __fastcall TRenderAPIChecker(RenderServiceParameters& rsp, TComponent* Owner);
};

extern PACKAGE TRenderAPIChecker *RenderAPIChecker;
//---------------------------------------------------------------------------
#endif

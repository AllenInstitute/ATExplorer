#ifndef TCreateMediansFormH
#define TCreateMediansFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "atATIFData.h"
#include <Vcl.ExtCtrls.hpp>
#include "atCreateMediansThread.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------

using at::ATIFData;
using at::CreateMediansThread;
//---------------------------------------------------------------------------
class PACKAGE TCreateMediansForm : public TForm
{
    __published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *RunBtn;
	TButton *CloseBtn;
	TProgressBar *PopulatePB;
	TGroupBox *GroupBox1;
	TLabel *ProgressLabel;
	TLabel *CurrentStateTbl;
	void __fastcall RunBtnClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

    private:
        ATIFData&       					mTheData;
		CreateMediansThread    				mTheThread;
        void								onThreadEnter(void*, 	void*, void*);
        void								onThreadProgress(void*, void*, void*);
        void								onThreadExit(void*, 	void*, void*);

    public:
        __fastcall TCreateMediansForm(ATIFData& data, TComponent* Owner);
};

extern PACKAGE TCreateMediansForm *CreateMediansForm;
#endif

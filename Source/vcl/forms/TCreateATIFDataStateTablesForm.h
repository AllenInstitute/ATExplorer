#ifndef TCreateATIFDataStateTablesFormH
#define TCreateATIFDataStateTablesFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "atATIFData.h"
#include <Vcl.ExtCtrls.hpp>
#include "atCreateATIFDataStateTablesThread.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------

using at::ATIFData;
using at::CreateATIFDataStateTablesThread;
//---------------------------------------------------------------------------
class PACKAGE TCreateATIFDataStateTablesForm : public TForm
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *NrOfRibbonsLbl;
        TLabel *NrOfSectionsLbl;
        TLabel *NrOfSessionsLbl;
        TLabel *NrOfTilesLbl;
        TLabel *Label5;
        TLabel *NrOfChannelsLbl;
        TLabel *Label6;
        TLabel *StateTablesLbl;
	TPanel *Panel1;
	TButton *RunBtn;
	TButton *CloseBtn;
	TProgressBar *PopulatePB;
	void __fastcall RunBtnClick(TObject *Sender);

    private:
        ATIFData&       					mTheData;
		CreateATIFDataStateTablesThread     mTheThread;
        void								onThreadEnter(void*, 	void*);
        void								onThreadProgress(void*, void*);
        void								onThreadExit(void*, 	void*);



    public:
        __fastcall TCreateATIFDataStateTablesForm(ATIFData& data, TComponent* Owner);
};

extern PACKAGE TCreateATIFDataStateTablesForm *CreateATIFDataStateTablesForm;
#endif

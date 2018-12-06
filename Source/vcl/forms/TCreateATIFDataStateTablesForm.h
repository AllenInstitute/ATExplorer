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
#include "atDockerContainer.h"
#include "dslTSTDStringLabeledEdit.h"
//---------------------------------------------------------------------------

using at::ATIFData;
using at::CreateATIFDataStateTablesThread;
using at::DockerContainer;
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
	TSTDStringLabeledEdit *DockerContainerE;
        void __fastcall RunBtnClick(TObject *Sender);
	void __fastcall DockerContainerEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


    private:
        ATIFData&       					mTheData;
		CreateATIFDataStateTablesThread     mTheThread;
        void								onThreadEnter(void*, 	void*, 	void*);
        void								onThreadProgress(void*, void*, 	void*);
        void								onThreadExit(void*, 	void*, 	void*);

    public:
        __fastcall 							TCreateATIFDataStateTablesForm(ATIFData& data, DockerContainer* dc, TComponent* Owner);
};

extern PACKAGE TCreateATIFDataStateTablesForm *CreateATIFDataStateTablesForm;
#endif

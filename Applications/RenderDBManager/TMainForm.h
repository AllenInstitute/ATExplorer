#ifndef TMainFormH
#define TMainFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include "dslTRegistryForm.h"
#include "dslTLogMemoFrame.h"
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "atRenderServiceParameters.h"
#include <Vcl.AppEvnts.hpp>
#include "dslTLogFileReader.h"
#include <Vcl.Menus.hpp>
#include "atGenericListOfPointers.h"
#include "pointMatches/atPointMatchCollection.h"
//---------------------------------------------------------------------------

using at::RenderServiceParameters;
using at::ListOfPointers;
using at::PointMatchCollection;

class TMainForm  : public TRegistryForm
{
    __published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TListBox *PMCollections;
	TButton *Button1;
	TPanel *BottomPanel;
	TSplitter *Splitter1;
	TPanel *PointMatchesPanel;
	TPanel *LeftPanel;
	TPanel *Panel1;
	TActionList *PointMatchActions;
	TPanel *Panel2;
	TComboBox *OwnersCB;
	TLabel *Label1;
	TAction *PopulateOwnersA;
	TAction *PopulateCollectionsForOwnerA;
	TApplicationEvents *ApplicationEvents1;
	TLogMemoFrame *LogMemoFrame1;
	TPopupMenu *PMCListPopup;
	TMenuItem *DeletePMCA;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall PopulateOwnersAExecute(TObject *Sender);
	void __fastcall OwnersCBCloseUp(TObject *Sender);
	void __fastcall PopulateCollectionsForOwnerAExecute(TObject *Sender);
	void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
	void __fastcall DeletePMCAClick(TObject *Sender);
	void __fastcall PMCollectionsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


    private:
    	RenderServiceParameters  				mRenderServiceParameters;


    public:
        __fastcall 								TMainForm(TComponent* Owner);
        __fastcall 								~TMainForm();
};

extern PACKAGE TMainForm *MainForm;
#endif

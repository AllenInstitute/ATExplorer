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
#include <Vcl.CheckLst.hpp>
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
	TActionList *RenderAPIActions;
	TPanel *Panel2;
	TComboBox *PMOwnersCB;
	TLabel *Label1;
	TAction *PopulatePointMatchOwnersA;
	TAction *PopulateCollectionsForOwnerA;
	TApplicationEvents *ApplicationEvents1;
	TLogMemoFrame *LogMemoFrame1;
	TPopupMenu *PMCListPopup;
	TMenuItem *DeletePMCA;
	TTabSheet *TabSheet2;
	TPanel *Panel3;
	TPanel *Panel4;
	TListBox *RenderProjectsLB;
	TPanel *Panel5;
	TButton *Button2;
	TPanel *Panel6;
	TLabel *Label2;
	TComboBox *RPOwnersCB;
	TAction *PopulateRPOwners;
	TAction *PopulateRPProjectsForOwnerA;
	TPopupMenu *RenderProjectsPopup;
	TMenuItem *MenuItem1;
	TAction *DeleteRenderProjectA;
	TAction *PopulateRenderStacksForProjectA;
	TCheckListBox *RenderStacksLB;
	TPopupMenu *StacksPopup;
	TMenuItem *MenuItem2;
	TAction *DeleteStackA;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall PopulatePointMatchOwnersAExecute(TObject *Sender);
	void __fastcall PMOwnersCBCloseUp(TObject *Sender);
	void __fastcall PopulateCollectionsForOwnerAExecute(TObject *Sender);
	void __fastcall ApplicationEvents1Exception(TObject *Sender, Exception *E);
	void __fastcall DeletePMCAClick(TObject *Sender);
	void __fastcall DeleteItem(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall PopulateRPOwnersExecute(TObject *Sender);
	void __fastcall PopulateRPProjectsForOwnerAExecute(TObject *Sender);
	void __fastcall DeleteRenderProjectAExecute(TObject *Sender);
	void __fastcall RenderProjectsLBClick(TObject *Sender);
	void __fastcall PopulateRenderStacksForProjectAExecute(TObject *Sender);
	void __fastcall DeleteStackAExecute(TObject *Sender);


    private:
    	RenderServiceParameters  				mRenderServiceParameters;


    public:
        __fastcall 								TMainForm(TComponent* Owner);
        __fastcall 								~TMainForm();
};

extern PACKAGE TMainForm *MainForm;
#endif

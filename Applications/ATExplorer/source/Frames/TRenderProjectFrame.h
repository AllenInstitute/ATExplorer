#ifndef TRenderProjectFrameH
#define TRenderProjectFrameH
#include "atRenderProject.h"
#include "dslTFloatLabeledEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <System.Classes.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include "atRenderClient.h"
//---------------------------------------------------------------------------
using at::RenderProject;
using at::RenderClient;
//---------------------------------------------------------------------------
class TRenderProjectFrame : public TFrame
{
    __published:	// IDE-managed Components
        TPanel *mLeftPanel;
        TScrollBox *ScrollBox1;
        TGroupBox *GroupBox1;
	TLabel *OwnerLabel;
	TLabel *ProjectLabel;
        TLabel *Label3;
        TComboBox *StackCB;
        TGroupBox *imageParasGB;
        TFloatLabeledEdit *mScaleE;
        TButton *mResetButton;
        TIntegerLabeledEdit *Width;
        TIntegerLabeledEdit *Height;
        TIntegerLabeledEdit *XCoordE;
        TIntegerLabeledEdit *YCoordE;
        TIntegerLabeledEdit *MaxIntensityE;
        TIntegerLabeledEdit *MinIntensityE;
        TFloatLabeledEdit *ScaleConstantE;
        TGroupBox *GroupBox9;
        TCheckListBox *ROI_CB;
        TPanel *Panel4;
        TButton *Button1;
        TPanel *ZsPanel;
        TGroupBox *Zs_GB;
        TCheckListBox *mZs;
        TGroupBox *CacheGB;
        TButton *FetchSelectedZsBtn;
        TButton *ClearCacheBtn;
        TGroupBox *GroupBox2;
        TCheckListBox *OtherCB;
        TGroupBox *GroupBox7;
        TCheckListBox *StacksCB;
        TPopupMenu *ZsPopUpMenu;
        TMenuItem *Checkrange1;
        TMenuItem *CheckAll1;
        TMenuItem *UncheckAll1;
        TMenuItem *CopyValidZs1;
        TMenuItem *CreateTiffStack1;
        TPopupMenu *StacksPopupMenu;
        TMenuItem *CreateMaxIntensityProjection1;
        TTimer *CreateCacheTimer;
        TIdHTTP *IdHTTP1;
	void __fastcall StackCBChange(TObject *Sender);
    private:
        RenderProject*              	mRP;
        RenderClient                    mRC;
        string                          mHostURL;
        void                            populate();

    public:
    						__fastcall 	TRenderProjectFrame(RenderProject* rp, TComponent* Owner);
		void 				__fastcall 	getValidZsForStack();


};

extern PACKAGE TRenderProjectFrame *RenderProjectFrame;
#endif

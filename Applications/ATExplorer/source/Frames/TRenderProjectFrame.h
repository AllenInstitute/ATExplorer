#ifndef TRenderProjectFrameH
#define TRenderProjectFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTFloatLabeledEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTPropertyCheckBox.h"
#include "dslTSTDStringLabeledEdit.h"
#include "RzSpnEdt.hpp"
#include "TAffineTransformationFrame.h"
#include "TRenderPythonRemoteScriptFrame.h"
#include "TSSHFrame.h"
#include <Vcl.CheckLst.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------


class TRenderProjectFrame : public TFrame
{
__published:	// IDE-managed Components
	TPageControl *ControlsPC;
	TTabSheet *TabSheet7;
	TPanel *mLeftPanel;
	TScrollBox *ScrollBox1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *OwnerCB;
	TComboBox *ProjectCB;
	TComboBox *StackCB;
	TGroupBox *GroupBox5;
	TRzSpinButtons *RzSpinButtons1;
	TFloatLabeledEdit *CustomImageRotationE;
	TCheckBox *ShowImageGridCB;
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
	TTabSheet *TransformsTab;
	TAffineTransformationFrame *TAffineTransformationFrame1;
	TTabSheet *TabSheet8;
	TPageControl *ScriptsPC;
	TTabSheet *TabSheet6;
	TGroupBox *StackGenerationGB;
	TLabel *Label4;
	TPropertyCheckBox *BoundsCB;
	TPropertyCheckBox *CreateTIFFStackCB;
	TPropertyCheckBox *DeleteTempTiffsCB;
	TPropertyCheckBox *PadFileNamesWithZeroesCB;
	TSTDStringLabeledEdit *SubFolder1;
	TSTDStringLabeledEdit *VolumesFolder;
	TFloatLabeledEdit *VolumesScaleE;
	TComboBox *ImageTypeCB;
	TMemo *BashScriptMemo;
	TGroupBox *MultiStackCreationGB;
	TCheckListBox *StacksForProjectCB;
	TGroupBox *GroupBox3;
	TPropertyCheckBox *CustomFilterCB;
	TEdit *CustomFilterE;
	TPanel *Panel2;
	TGroupBox *JobCreationGB;
	TIntegerLabeledEdit *ZBatchSizeE;
	TIntegerLabeledEdit *MaxNumberOfRemoteJobsE;
	TIntegerLabeledEdit *NicenessE;
	TButton *Run;
	TTabSheet *TabSheet9;
	TGroupBox *GroupBox4;
	TSTDStringLabeledEdit *BaseURLE;
	TButton *TestRenderServiceBtn;
	TIntegerLabeledEdit *maxTileSpecsToRenderE;
	TIntegerLabeledEdit *RenderPort;
	TGroupBox *TestSSHGB;
	TButton *CMDButton;
	TEdit *mCMD;
	TSSHFrame *TSSHFrame1;
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
private:	// User declarations
public:		// User declarations
	__fastcall TRenderProjectFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRenderProjectFrame *RenderProjectFrame;
//---------------------------------------------------------------------------
#endif

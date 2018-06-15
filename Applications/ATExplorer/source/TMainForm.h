#ifndef TMainFormH
#define TMainFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "dslTFloatLabeledEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.CheckLst.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "dslLogFileReader.h"
#include "dslLogLevel.h"
#include <Vcl.ComCtrls.hpp>
#include "dslTIntLabel.h"
#include "dslTPropertyCheckBox.h"
#include "atRenderClient.h"
#include "atROIHistory.h"
//#include "dslProcess.h"
#include "dslIniFileProperties.h"
#include "dslRegistryProperties.h"
#include "dslTIniFileC.h"
#include "dslApplicationProperties.h"
#include "atFetchImagesThread.h"
#include <Vcl.Menus.hpp>
#include "dslTIntegerEdit.h"
#include "TSSHFrame.h"
#include "TImageControlsFrame.h"
#include "MagickWand/MagickWand.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ImgList.hpp>
#include "atProjectManager.h"
#include <System.ImageList.hpp>
#include "dslTRegistryForm.h"
#include "dslTFloatLabeledEdit.h"
#include "dslTIniFileC.h"
#include "dslTIntegerEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTIntLabel.h"
#include "dslTPropertyCheckBox.h"
#include "dslTSTDStringLabeledEdit.h"
#include "DcefB.Core.DcefBrowser.hpp"
class TImageForm;
//using dsl::Process;
//---------------------------------------------------------------------------
using dsl::IniFileProperties;
using dsl::TRegistryProperties;
using dsl::ApplicationProperties;
using dsl::shared_ptr;
extern string gApplicationRegistryRoot;
void brightnessContrast(TImage *imageSelected);
string createProcessedImageFileName(const string& fname);

class ATExplorerProject;

class TMainForm : public TRegistryForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TMemo *infoMemo;
	TIdHTTP *IdHTTP1;
	TTimer *mShutDownTimer;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TGroupBox *Zs_GB;
	TFloatLabeledEdit *mScaleE;
	TSplitter *Splitter1;
	TPanel *mBottomPanel;
	TGroupBox *imageParasGB;
	TButton *mResetButton;
	TButton *mHistoryBackBtn;
	TButton *mHistoryFFW;
	TPanel *mLeftPanel;
	TPaintBox *PaintBox1;
	TIniFileC *mIniFileC;
	TPanel *Panel2;
	TButton *mCLearMemo;
	TSplitter *Splitter2;
	TPopupMenu *ZsPopUpMenu;
	TMenuItem *CopyValidZs1;
	TButton *mZoomOutBtn;
	TButton *mZoomInBtn;
	TIntegerLabeledEdit *Width;
	TIntegerLabeledEdit *Height;
	TIntegerLabeledEdit *XCoord;
	TIntegerLabeledEdit *YCoord;
	TButton *mCloseBottomPanelBtn;
	TIntegerEdit *mZoomFactor;
	TButton *mShowBottomPanelBtn;
	TTabSheet *TabSheet3;
	TButton *mBrowseForCacheFolder;
	TSTDStringLabeledEdit *mImageCacheFolderE;
	TGroupBox *GroupBox6;
	TPanel *mLogPanel;
	TPanel *Panel5;
	TIntLabel *mXC;
	TIntLabel *mYC;
	TIntLabel *mX;
	TIntLabel *mY;
	TGroupBox *GroupBox8;
	TGroupBox *GroupBox9;
	TButton *mFetchSelectedZsBtn;
	TSSHFrame *TSSHFrame1;
	TTabSheet *TabSheet4;
	TGroupBox *StackGenerationGB;
	TButton *Run;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Help1;
	TMenuItem *About1;
	TGroupBox *GroupBox4;
	TSTDStringLabeledEdit *mBaseUrlE;
	TMemo *BashScriptMemo;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *OwnerCB;
	TComboBox *ProjectCB;
	TComboBox *StackCB;
	TGroupBox *TestSSHGB;
	TButton *CMDButton;
	TEdit *mCMD;
	TTimer *CreateCacheTimer;
	TIntegerLabeledEdit *MaxIntensity;
	TIntegerLabeledEdit *MinIntensity;
	TScrollBox *ScrollBox1;
	TGroupBox *CacheGB;
	TGroupBox *PostProcessingGB;
	TCheckBox *IMContrastControl;
	TCheckListBox *StacksForProjectCB;
	TGroupBox *MultiStackCreationGB;
	TPropertyCheckBox *BoundsCB;
	TFloatLabeledEdit *VolumesScaleE;
	TSTDStringLabeledEdit *VolumesFolder;
	TSTDStringLabeledEdit *SubFolder1;
	TGroupBox *GroupBox2;
	TButton *OpenInNDVIZBtn;
	TPopupMenu *ImagePopup;
	TMenuItem *ParseNDVIZURL1;
	TButton *OpenFromNDVIZBtn;
	TCheckListBox *mZs;
	TMenuItem *CheckAll1;
	TMenuItem *UncheckAll1;
	TMenuItem *Checkrange1;
	TMenuItem *Exit1;
	TGroupBox *GroupBox3;
	TMenuItem *Options1;
	TMenuItem *ThemesMenu;
	TCheckBox *FlipImageRightCB;
	TRadioGroup *ColorRG;
	TStatusBar *StatusBar1;
	TPropertyCheckBox *CustomFilterCB;
	TEdit *CustomFilterE;
	TMenuItem *OpenaClone1;
	TCheckBox *FlipImageLeftCB;
	THeaderControl *HeaderControl1;
	TPanel *Panel1;
	TMenuItem *AddOverlayedImage1;
	TPropertyCheckBox *CreateTIFFStackCB;
	TPropertyCheckBox *DeleteTempTiffsCB;
	TIntegerLabeledEdit *ZBatchSizeE;
	TIntegerLabeledEdit *MaxNumberOfRemoteJobsE;
	TIntegerLabeledEdit *NicenessE;
	TGroupBox *JobCreationGB;
	TMenuItem *Open1;
	TActionList *MenuActions;
	TFileOpen *FileOpen1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TMenuItem *New1;
	TAction *NewProjectA;
	TSaveDialog *SaveDialog1;
	TAction *SaveProjectA;
	TMenuItem *Save1;
	TAction *SaveProjectAsA;
	TMenuItem *SaveAs1;
	TAction *CloseProjectA;
	TMenuItem *Close1;
	TImageList *ImageList1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TPanel *ProjectManagerPanel;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *Reopen;
	TMenuItem *N3;
	TTreeView *ProjectTView;
	TPanel *ProjFilePathPanel;
	TLabel *ProjFileLbl;
	TPopupMenu *ProjTreeViewPopup;
	TAction *AddRenderProject;
	TMenuItem *AddRenderProject1;
	TMenuItem *Close2;
	TPanel *MainPanel;
	TAction *EditViewNode;
	TPropertyCheckBox *PadFileNamesWithZeroesCB;
	TComboBox *ImageTypeCB;
	TLabel *Label4;
	TFloatLabeledEdit *ScaleConstantE;
	TFloatLabeledEdit *CustomRotationE;
	TButton *TestRenderServiceBtn;
	TPageControl *PageControl2;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet5;
	TDcefBrowser *DcefBrowser1;
	void __fastcall ClickZ(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall mShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall mScaleEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall resetButtonClick(TObject *Sender);
	void __fastcall historyBtnClick(TObject *Sender);
	void __fastcall TraverseZClick(TObject *Sender);
	void __fastcall mFetchSelectedZsBtnClick(TObject *Sender);
	void __fastcall mGetValidZsBtnClick(TObject *Sender);
	void __fastcall mBrowseForCacheFolderClick(TObject *Sender);
	void __fastcall mCLearMemoClick(TObject *Sender);
	void __fastcall mUpdateZsBtnClick(TObject *Sender);
	void __fastcall CopyValidZs1Click(TObject *Sender);
	void __fastcall GetOptimalBoundsBtnClick(TObject *Sender);
	void __fastcall mZoomBtnClick(TObject *Sender);
	void __fastcall OwnerCBChange(TObject *Sender);
	void __fastcall ProjectCBChange(TObject *Sender);
	void __fastcall mCloseBottomPanelBtnClick(TObject *Sender);
	void __fastcall mShowBottomPanelBtnClick(TObject *Sender);
	void __fastcall StackCBChange(TObject *Sender);
	void __fastcall TSSHFrame1ScSSHShell1AsyncReceive(TObject *Sender);
	void __fastcall CMDButtonClick(TObject *Sender);
	void __fastcall RunClick(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall TSSHFrame1ScSSHClientAfterConnect(TObject *Sender);
	void __fastcall TSSHFrame1ScSSHClientAfterDisconnect(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CreateCacheTimerTimer(TObject *Sender);
	void __fastcall OpenInNDVIZBtnClick(TObject *Sender);
	void __fastcall IntensityKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ParseNDVIZURL1Click(TObject *Sender);
	void __fastcall CreateNDVIZURL1Click(TObject *Sender);
	void __fastcall CheckAll1Click(TObject *Sender);
	void __fastcall UncheckAll1Click(TObject *Sender);
	void __fastcall Checkrange1Click(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall StackFilterCBClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ThemesMenuClick(TObject *Sender);
	void __fastcall ClickImageProcCB(TObject *Sender);
	void __fastcall ColorRGClick(TObject *Sender);
	void __fastcall CustomFilterEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall OpenaClone1Click(TObject *Sender);
	void __fastcall AddOverlayedImage1Click(TObject *Sender);
	void __fastcall CreateTIFFStackCBClick(TObject *Sender);
	void __fastcall NewProjectAExecute(TObject *Sender);
	void __fastcall ProjectStatusTimerTimer(TObject *Sender);
	void __fastcall FileOpen1Accept(TObject *Sender);
	void __fastcall CloseProjectAExecute(TObject *Sender);
	void __fastcall CloseProjectAUpdate(TObject *Sender);
	void __fastcall SaveProjectAsAUpdate(TObject *Sender);
	void __fastcall SaveProjectAUpdate(TObject *Sender);
	void __fastcall SaveProjectAExecute(TObject *Sender);
	void __fastcall SaveProjectAsAExecute(TObject *Sender);
	void __fastcall AddRenderProjectExecute(TObject *Sender);
	void __fastcall ProjectTViewContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled);
	void __fastcall ProjectTViewEditing(TObject *Sender, TTreeNode *Node, bool &AllowEdit);
	void __fastcall ProjectTViewEdited(TObject *Sender, TTreeNode *Node, UnicodeString &S);
	void __fastcall EditViewNodeExecute(TObject *Sender);
	void __fastcall ProjectTViewClick(TObject *Sender);
	void __fastcall CustomRotationEKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall TestRenderServiceBtnClick(TObject *Sender);
	void __fastcall DcefBrowser1BeforeBrowse(ICefBrowser * const browser, ICefFrame * const frame,
          ICefRequest * const request, bool isRedirect, bool &Cancel);
	void __fastcall DcefBrowser1ConsoleMessage(ICefBrowser * const browser, const ustring message,
          const ustring source, int line, bool &Cancel);
	void __fastcall DcefBrowser1StateChange(ICefBrowser * const browser, const TBrowserDataChangeKind Kind,
          const UnicodeString Value);



	private:	// User declarations
       	void __fastcall 								DrawShape(TPoint TopLeft, TPoint BottomRight, TPenMode AMode);
        RenderClient									mRC;
        int												getCurrentZ();
		bool        									mRenderEnabled;

        void __fastcall                                 logMsg();
		LogFileReader                                   mLogFileReader;
		bool          									mIsStyleMenuPopulated;
        ApplicationProperties                           mAppProperties;
        shared_ptr<IniFileProperties>              		mGeneralProperties;
        Property<int>	                            	mBottomPanelHeight;
		Property<dsl::LogLevel>	                		mLogLevel;
		Property<string>	 		                	mCurrentProject;
		Property<string>	 		                	mCurrentOwner;
		Property<string>	 		                	mCurrentStack;

        shared_ptr<IniFileProperties>                   mServer1Properties;
        shared_ptr<IniFileProperties>                   mServer2Properties;
        bool                                            setupAndReadIniParameters();
        void                                            setupIniFile();
		double 											getImageStretchFactor();
        void											updateScale();

        //Drawing stuff
        TBrushStyle 									BrushStyle;
        TPenStyle 										PenStyle;
        int 											PenWide;
        bool 											Drawing;
        TPoint 											Origin;
        TPoint 											MovePt;
        TPoint											mTopLeftSelCorner;
        TPoint											mBottomRightSelCorner;
		void								            render(RenderBox* box = NULL);

        //Render areas history
	    ROIHistory										mROIHistory;
		RenderBox										mCurrentRB;
      	TCanvas*										getCanvas();

		FetchImagesThread								mCreateCacheThread;
        string											createNDVIZURL();
		void __fastcall 								onImage();

        //Remote jobs
		string 											createRemoteCommand(const string& remoteScript, const string& stack);
		string 											createEmptyScriptFileOnServer(const string& stack);
		bool                							populateRemoteScript(const string& script);
        void 											runJob(const string& job);
        void											applyContrastControl(MagickWand *image_wand);
		void 											flipImage(MagickWand *image_wand, int deg);
		void 											colorImage(MagickWand *image_wand, int colorIndex);

	    TImageForm*										gImageForm;
        string 											mCurrentImageFile;

        												//!VC can have only one VC project open at any one time.
		ProjectManager									mProjectManager;
		ATExplorerProject*							getCurrentVCProject();

        vector<ATExplorerProject*>					mVCProjects;
		int __fastcall 									saveProject();
		int __fastcall 									saveProjectAs();
		int __fastcall 									closeProject();
		ATExplorerProject* __fastcall 				createNewProject();

public:
	__fastcall 											TMainForm(TComponent* Owner);
	__fastcall 											~TMainForm();
};

extern PACKAGE TMainForm *MainForm;
#endif

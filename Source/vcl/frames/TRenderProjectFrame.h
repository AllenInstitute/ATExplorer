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
#include "dslTIntegerEdit.h"
#include "dslTSTDStringEdit.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "atRegionOfInterest.h"
#include "RzSpnEdt.hpp"
#include "dslTSTDStringLabeledEdit.h"
#include "atFetchImagesThread.h"
#include "atFetchImageThread.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include "dslProcess.h"
#include "atImageGrid.h"
#include "atATExplorer.h"
#include "atTiffStackCreator.h"
//---------------------------------------------------------------------------


class TCreateLocalVolumesForm;

using at::RenderProject;
using at::RenderClient;
using at::RegionOfInterest;
using at::FetchImagesThread;
using at::FetchImageThread;
using dsl::Process;
using at::ImageGrid;
using at::ATExplorer;
using at::TiffStackCreator;
//---------------------------------------------------------------------------
class PACKAGE TRenderProjectFrame : public TFrame
{
    __published:	// IDE-managed Components
        TPanel *mLeftPanel;
        TScrollBox *ScrollBox1;
        TGroupBox *GroupBox1;
        TLabel *Label3;
        TComboBox *StackCB;
        TGroupBox *imageParasGB;
        TFloatLabeledEdit *mScaleE;
	TButton *ResetButton;
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
        TPopupMenu *ZsPopUpMenu;
	TMenuItem *CheckAll;
	TMenuItem *UnCheckAll;
        TMenuItem *CreateTiffStack1;
        TPopupMenu *StacksPopupMenu;
        TMenuItem *CreateMaxIntensityProjection1;
        TTimer *CreateCacheTimer;
        TIdHTTP *IdHTTP1;
	TPageControl *VisualsPC;
	TTabSheet *TabSheet2;
	TPanel *Panel1;
	TPaintBox *PaintBox1;
	TImage *Image1;
	TLabel *XE;
	TLabel *YE;
	THeaderControl *HeaderControl1;
	TIntegerEdit *mZoomFactor;
	TSTDStringEdit *URLE;
	TTabSheet *NdVizTS;
	TButton *ClearBrowserCacheBtn;
	TGroupBox *GroupBox5;
	TRzSpinButtons *RzSpinButtons1;
	TFloatLabeledEdit *CustomImageRotationE;
	TPopupMenu *ImagePopup;
	TMenuItem *openInChrome;
	TSTDStringLabeledEdit *OwnerE;
	TSTDStringLabeledEdit *ProjectE;
	TAction *CreateTiffStackA;
	TActionList *Actions;
	TAction *CreateMIPA;
	TMenuItem *OpenStackInExplorer;
	TAction *OpenInExplorerA;
	TMenuItem *OpenSectionInExplorer;
	TPopupMenu *OtherPopupMenu;
	TMenuItem *OpenMIPInExplorer;
	TPopupMenu *ROIPopupMenu;
	TMenuItem *OpenROIInExplorer;
	TAction *ToggleImageGridA;
	TCheckListBox *ChannelsCB;
	TGroupBox *GroupBox3;
	TPopupMenu *RenderStacksPopup;
	TCheckListBox *OtherCB;
	TGroupBox *GroupBox2;
	TCheckListBox *StacksCB;
	TAction *CreateSubVolumeStackA;
	TSTDStringLabeledEdit *RenderHostE;
	TPopupMenu *MiscPopup;
	TMenuItem *CreateSubVolume1;
	TCheckBox *ShowImageGridCB;
	TButton *Button2;
		void __fastcall StackCBChange(TObject *Sender);
	void __fastcall ClickZ(TObject *Sender);
	void __fastcall ResetButtonClick(TObject *Sender);
	void __fastcall MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);

	void __fastcall IntensityKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ROIKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall openInChromeClick(TObject *Sender);
	void __fastcall FetchSelectedZsBtnClick(TObject *Sender);
	void __fastcall CreateTiffStackExecute(TObject *Sender);
	void __fastcall CreateMIPAExecute(TObject *Sender);
	void __fastcall CheckBoxClick(TObject *Sender);
	void __fastcall ROI_CBClick(TObject *Sender);
	void __fastcall OpenInExplorerAExecute(TObject *Sender);

	void __fastcall RzSpinButtons1DownLeftClick(TObject *Sender);
	void __fastcall RzSpinButtons1UpRightClick(TObject *Sender);
	void __fastcall ToggleImageGridAExecute(TObject *Sender);
	void __fastcall ToggleImageGridAUpdate(TObject *Sender);
	void __fastcall PaintBox1Paint(TObject *Sender);
	void __fastcall OtherCBDblClick(TObject *Sender);
	void __fastcall MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall CreateCacheTimerTimer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall openVolumesForm(TObject *Sender);

	void __fastcall ChannelsCBClick(TObject *Sender);
	void __fastcall ChannelsCBClickCheck(TObject *Sender);
	void __fastcall HeaderControl1SectionClick(THeaderControl *HeaderControl, THeaderSection *Section);
	void __fastcall Panel1ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall TabSheet2ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall StacksCBClick(TObject *Sender);

	void __fastcall Checkrange1Click(TObject *Sender);
	void __fastcall CheckZs(TObject *Sender);
	void __fastcall CreateSubVolumeStackAExecute(TObject *Sender);
	void __fastcall HeaderControl1ContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled);
	void __fastcall Button2Click(TObject *Sender);

    private:
        string                                          mIMPath;
        TiffStackCreator                                mTiffStackCreator;
        ImageGrid                                       mImageGrid;
        ATExplorer&                                     mExplorer;

                                                        //A Reference to a render project
        RenderProject&			     	                mRP;
        RenderClient                                    mRC;
   		FetchImagesThread								mCreateCacheThread;
   		bool        									mRenderEnabled;
        string 											mCurrentImageFile;

        //Render areas history
		RegionOfInterest								mCurrentROI;
        string                                          mHostURL;
        string                                          getCurrentROIPath();
        void                                            populate();
		void __fastcall 								onImage();
		void 											paintRotatedImage(double angle);

        void 											onROIChanged(void* arg1, void* arg2);
        void __fastcall 								roiChanged();
		void 											checkCache();
		int												getCurrentZ();
		void 											updateScale();
		void 											updateROIs();
		double 											getImageStretchFactor();
		TCanvas* 										getCanvas();

        //Drawing stuff
        TBrushStyle 									BrushStyle;
        TPenStyle 										PenStyle;
        int 											PenWide;
        bool 											mIsDrawing;
        TPoint 											Origin;
        TPoint 											MovePt;
        TPoint											mTopLeftSelCorner;
        TPoint											mBottomRightSelCorner;
		void 											DrawShape(TPoint TopLeft, TPoint BottomRight, TPenMode AMode);
		string 											createNDVIZURL();

                                                        //Make this nicer later on
	    Process 										mAProcess;
        void                                            onIMProcessFinished(void*, void*);
		void 											OpenImageForm(string fName);

		TCreateLocalVolumesForm*                        mCreateVolumesForm;
        void                                            zoom(int factor, bool inOrOut);

    public:
    						__fastcall 					TRenderProjectFrame(ATExplorer& e, RenderProject& rp, TComponent* Owner);
		void 				__fastcall 					getValidZsForStack();

};

extern PACKAGE TRenderProjectFrame *RenderProjectFrame;
#endif

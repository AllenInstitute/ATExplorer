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
	TPageControl *VisualsPC;
	TTabSheet *TabSheet2;
	TPanel *Panel1;
	TPaintBox *PaintBox1;
	TImage *Image1;
	TLabel *XE;
	TLabel *YE;
	THeaderControl *HeaderControl1;
	TIntegerEdit *mZoomFactor;
	TButton *mZoomInBtn;
	TButton *mZoomOutBtn;
	TSTDStringEdit *URLE;
	TTabSheet *NdVizTS;
	TButton *ClearBrowserCacheBtn;
	TGroupBox *GroupBox5;
	TRzSpinButtons *RzSpinButtons1;
	TFloatLabeledEdit *CustomImageRotationE;
	TCheckBox *ShowImageGridCB;
	TPopupMenu *ImagePopup;
	TMenuItem *OpenaClone1;
	TMenuItem *openInChrome;
	TMenuItem *ToggleImageGridMI;
	TMenuItem *HideLogWindow1;
	TSTDStringLabeledEdit *OwnerE;
	TSTDStringLabeledEdit *ProjectE;
		void __fastcall StackCBChange(TObject *Sender);
	void __fastcall ClickZ(TObject *Sender);
	void __fastcall ResetButtonClick(TObject *Sender);
	void __fastcall FrameMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall IntensityKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FrameMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ROIKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);




    private:
        RenderProject*			     	                mRP;
        RenderClient                                    mRC;
   		bool        									mRenderEnabled;
        string 											mCurrentImageFile;

        //Render areas history
		RegionOfInterest								mCurrentROI;
        string                                          mHostURL;
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
        bool 											Drawing;
        TPoint 											Origin;
        TPoint 											MovePt;
        TPoint											mTopLeftSelCorner;
        TPoint											mBottomRightSelCorner;
		void 											DrawShape(TPoint TopLeft, TPoint BottomRight, TPenMode AMode);


    public:
    						__fastcall 	TRenderProjectFrame(RenderProject* rp, TComponent* Owner);
		void 				__fastcall 	getValidZsForStack();

};

extern PACKAGE TRenderProjectFrame *RenderProjectFrame;
#endif

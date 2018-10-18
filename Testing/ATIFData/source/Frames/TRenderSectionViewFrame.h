#ifndef TRenderSectionViewFrameH
#define TRenderSectionViewFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerEdit.h"
#include "dslTSTDStringEdit.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TRenderSectionViewFrame : public TFrame
{
__published:	// IDE-managed Components
	TPanel *CenterPanel;
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
	TPopupMenu *ImagePopup;
	TMenuItem *OpenaClone1;
	TMenuItem *openInChrome;
	TMenuItem *ToggleImageGridMI;
	TMenuItem *HideLogWindow1;
private:	// User declarations
public:		// User declarations
	__fastcall TRenderSectionViewFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRenderSectionViewFrame *RenderSectionViewFrame;
//---------------------------------------------------------------------------
#endif

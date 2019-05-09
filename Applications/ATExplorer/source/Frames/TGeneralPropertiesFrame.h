#ifndef TGeneralPropertiesFrameH
#define TGeneralPropertiesFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerLabeledEdit.h"
#include "dslTPropertyCheckBox.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslProperties.h"
#include "atATExplorer.h"
//---------------------------------------------------------------------------

using dsl::Properties;
using at::ATExplorer;
//---------------------------------------------------------------------------
class PACKAGE TGeneralPropertiesFrame : public TFrame
{
    __published:	// IDE-managed Components
	TGroupBox *GroupBox2;
	TSTDStringLabeledEdit *ImageMagickPathE;
	TButton *BrowseForImageMagickPathBtn;
	TGroupBox *GroupBox3;
	TLabel *Label8;
	TComboBox *RenderServicesCB;
    void __fastcall BrowseForFolderClick(TObject *Sender);
	void __fastcall TestRenderServiceBtnClick(TObject *Sender);

    private:
        ATExplorer&             mExplorer;

    public:
        			__fastcall 	TGeneralPropertiesFrame(ATExplorer& e, TComponent* Owner);
        bool                	populate(Properties& props);
};

extern PACKAGE TGeneralPropertiesFrame *GeneralPropertiesFrame;
#endif

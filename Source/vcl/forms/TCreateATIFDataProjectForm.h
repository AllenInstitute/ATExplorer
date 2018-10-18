#ifndef TCreateATIFDataProjectFormH
#define TCreateATIFDataProjectFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------


class PACKAGE TCreateATIFDataProjectForm : public TForm
{
    __published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
		TGroupBox *GroupBox3;
		TSTDStringLabeledEdit *DataRootFolderE;
		TButton *BrowseForDataOutputPathBtn;
		void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
		void __fastcall BrowseForDataOutputPathBtnClick(TObject *Sender);

    private:

    public:
        					__fastcall 	TCreateATIFDataProjectForm(TComponent* Owner);
        string                          getDataRootFolderLocation();
};

extern PACKAGE TCreateATIFDataProjectForm *CreateATIFDataProjectForm;

#endif

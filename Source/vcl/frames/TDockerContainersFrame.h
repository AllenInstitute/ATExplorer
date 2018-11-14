#ifndef TDockerContainersFrameH
#define TDockerContainersFrameH
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
#include <Vcl.Menus.hpp>
#include "dslPropertiesContainer.h"
//---------------------------------------------------------------------------

namespace at
{
	class DockerContainer;
}

using dsl::Properties;
using at::ATExplorer;
using at::DockerContainer;


//---------------------------------------------------------------------------
class PACKAGE TDockerContainersFrame : public TFrame
{
    __published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox4;
        TButton *TestBtn;
        TListBox *ItemsLB;
        TPanel *Panel1;
        TButton *AddBtn;
        TButton *RemoveBtn;
        TPopupMenu *PopupMenu1;
        TMenuItem *Rename;

	void __fastcall TestBtnClick(TObject *Sender);
	void __fastcall AddBtnClick(TObject *Sender);
	void __fastcall ItemsLBClick(TObject *Sender);
	void __fastcall RenameClick(TObject *Sender);
	void __fastcall RemoveBtnClick(TObject *Sender);

    private:
		ATExplorer& 				mExplorer;

                                	//New services are a special case
        dsl::PropertiesContainer  	mNewContainers;
	    DockerContainer*  			getCurrent();

    public:
        			__fastcall 		TDockerContainersFrame(ATExplorer& e, TComponent* Owner);
        bool                		populate();
        bool                    	applyEditsForNewServices();

};

extern PACKAGE TDockerContainersFrame *DockerContainersFrame;
#endif

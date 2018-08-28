#ifndef TMainFormH
#define TMainFormH
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "dslTLogMemoFrame.h"
#include "atProjectManager.h"
#include "dslTRegistryForm.h"
#include "atProjectsTreeView.h"
#include "dslObserver.h"
#include <memory>
#include "atRenderProjectView.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

//typedef void __fastcall (__closure *sshCallback)(const string&);
using at::ProjectManager;
using at::ProjectsTreeView;
using at::ATExplorerProject;
using at::RenderProjectView;
using dsl::Project;
using dsl::Observer;
using dsl::shared_ptr;
using std::vector;


class PACKAGE TMainForm : public TRegistryForm
{
__published:	// IDE-managed Components
	TTimer *ShutDownTimer;
	TPanel *BottomPanel;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Help1;
	TMenuItem *About1;
	TMenuItem *Exit1;
	TMenuItem *Options1;
	TMenuItem *ThemesMenu;
	TStatusBar *StatusBar1;
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
	TMenuItem *ReopenMenu;
	TMenuItem *N3;
	TTreeView *ProjectTView;
	TPopupMenu *ProjTreeViewPopup;
	TAction *AddRenderProject;
	TMenuItem *AddRenderProject1;
	TMenuItem *Close2;
	TPanel *MainPanel;
	TAction *EditViewNode;
	TPanel *TopPanel2;
	TPanel *Panel3;
	TButton *ShowBottomPanelBtn;
	TSplitter *Splitter2;
	TPopupMenu *PopupMenu1;
	TAction *ToggleBottomPanelA;
	TMenuItem *Action11;
	TToolButton *ToolButton4;
	TAction *ToggleImageGridA;
	TAction *CreateTiffStackA;
	TAction *CreateMIPA;
	TLogMemoFrame *TLogMemoFrame1;
	TAction *OpenSettingsA;
	TMenuItem *Settings1;
	TToolButton *ToolButton6;
	TSplitter *Splitter1;
	TFileExit *FileExit1;
	TToolButton *ToolButton7;
	TMenuItem *ProjectOptions1;
	TPageControl *MainPC;
	TPopupMenu *MainPCPopup;
	TMenuItem *Close3;
	TMenuItem *Properties1;
	TAction *RemoveFromProjectA;
	TMenuItem *RemoveFromProject1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ThemesMenuClick(TObject *Sender);
	void __fastcall NewProjectAExecute(TObject *Sender);
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
	void __fastcall ToggleBottomPanelAExecute(TObject *Sender);
	void __fastcall ToggleBottomPanelAUpdate(TObject *Sender);
	void __fastcall OpenSettingsAExecute(TObject *Sender);
	void __fastcall ProjTreeViewPopupPopup(TObject *Sender);
	void __fastcall ProjectTViewDblClick(TObject *Sender);
	void __fastcall MainPCContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall Close3Click(TObject *Sender);
	void __fastcall RemoveFromProjectAExecute(TObject *Sender);

	private:
		bool          									mIsStyleMenuPopulated;
        bool                                            setupAndReadIniParameters();
        bool        									createProjectView(Project* p);
	    ProjectsTreeView                                mPV;

        //Should really be unique ptrs
        vector< shared_ptr< RenderProjectView> >        mObservers;

		int 		 									saveProject(Project* p);
		int			 									saveProjectAs(Project* p);

	public:
		__fastcall 			  							TMainForm(TComponent* Owner);
		__fastcall 			  							~TMainForm();


	BEGIN_MESSAGE_MAP
//		MESSAGE_HANDLER(FINISHED_RENDER_ROTATE,	    	TextMessage,		onFinishedRenderRotate);
	END_MESSAGE_MAP(TForm)
};

extern PACKAGE TMainForm *MainForm;
#endif

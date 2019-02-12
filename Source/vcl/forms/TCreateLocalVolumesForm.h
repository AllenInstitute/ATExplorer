#ifndef TCreateLocalVolumesFormH
#define TCreateLocalVolumesFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTFloatLabeledEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include <Vcl.CheckLst.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "atRenderProject.h"
#include "atRegionOfInterest.h"
#include "atRenderClient.h"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "dslStringList.h"
#include "atFetchImagesThread.h"
#include "dslTPropertyCheckBox.h"
#include <map>
//---------------------------------------------------------------------------

using at::RenderProject;
using at::RegionOfInterest;
using at::RenderClient;
using at::FetchImagesThread;
using dsl::StringList;
using std::map;
class TCreateStackThreadFrame;

namespace at
{
	class TiffStack;
}


typedef map< shared_ptr<FetchImagesThread>, shared_ptr<TCreateStackThreadFrame> > ThreadFrameThreadContainer;
//---------------------------------------------------------------------------
class PACKAGE TCreateLocalVolumesForm : public TForm
{
	typedef boost::function<void(void*, void*)> FITCallBack;
    __published:	// IDE-managed Components
        TPanel *Panel1;
		TButton *RunBtn;
        TButton *Button2;
        TCheckListBox *RenderStacksCB;
        TGroupBox *imageParasGB;
        TFloatLabeledEdit *mScaleE;
        TIntegerLabeledEdit *Width;
        TIntegerLabeledEdit *Height;
        TIntegerLabeledEdit *XCoordE;
        TIntegerLabeledEdit *YCoordE;
        TIntegerLabeledEdit *MaxIntensityE;
        TIntegerLabeledEdit *MinIntensityE;
        TPanel *Panel2;
        TGroupBox *GroupBox1;
        TLabel *Label4;
        TComboBox *ImageTypeCB;
	TRadioGroup *ImageTypeRG;
	TGroupBox *Zs_GB;
	TCheckListBox *mZs;
	TTimer *CreateStacksTimer;
	TPanel *MainPanel;
	TScrollBox *ThreadsPanel;
	TPropertyCheckBox *RemoveSectionsCB;
	TSplitter *Splitter1;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ImageTypeRGClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall RunBtnClick(TObject *Sender);
	void __fastcall RenderStacksCBClick(TObject *Sender);
	void __fastcall CreateStacksTimerTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

    private:
                                            //A New TiffStack becomes part of this project
        RenderProject&         		        mRP;
        RegionOfInterest       	            mROI;
        RenderClient                        mRC;
		StringList 				            getValidZsForStack(const string& stackName);
        string                              mImageMagickPath;
        string                              mConvertExe;

		ThreadFrameThreadContainer          mThreads;
        int                                 getNumberOfRunningThreads();
        shared_ptr<TCreateStackThreadFrame> createThreadFrame(shared_ptr<FetchImagesThread> t);
        void								onThreadEnter(void*, 	void*);
        void								onThreadProgress(void*, void*);
        void								onThreadExit(void*, 	void*);
        TCreateStackThreadFrame*			getFrameForRawThread(FetchImagesThread* t);
        at:: TiffStack*                     createTiffStack(const StringList& l, const string& wd, const string& outFolder);
        string                              getImageType();
        void                                populateZs(const string& stack);

    public:
				     __fastcall             TCreateLocalVolumesForm(RenderProject& rp, const string& imageMagickPath, TComponent* Owner);
        void					            populate(const RegionOfInterest& roi, const StringList& stacks);
};

extern PACKAGE TCreateLocalVolumesForm *CreateLocalVolumesForm;

#endif

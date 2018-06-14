#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "atRenderClient.h"
#include "atROIHistory.h"
#include "dslRestartApplicationUtils.h"
#include "TAboutVolumeCreatorForm.h"
//---------------------------------------------------------------------------

using namespace dsl;
extern string gAppName;
extern string gApplicationStyle;
extern string gRestartMutexName;

void __fastcall TMainForm::logMsg()
{
    infoMemo->Lines->Add(vclstr(mLogFileReader.getData()));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::About1Click(TObject *Sender)
{
	TAboutVolumeCreator* a = new TAboutVolumeCreator(this);
	a->ShowModal();
    delete a;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void __fastcall TMainForm::ThemesMenuClick(TObject *Sender)
{

   TMenuItem* menuItem = dynamic_cast<TMenuItem*>(Sender);
    if(!menuItem)
    {
        return;
    }

	//Uncheck any checked items
	for(int i = 0; i < ThemesMenu->Count; i++)
	{
		TMenuItem* menuItem = ThemesMenu->Items[i];
		if(menuItem && menuItem->Checked)
		{
			menuItem->Checked = false;
		}
	}

	TRegistryForm::writeToRegistry();

    DcefBrowser1->Visible = false;

	TReplaceFlags rFlags(rfIgnoreCase|rfReplaceAll);
	String styleName = StringReplace(menuItem->Caption, "&", "", rFlags);
	TStyleManager::SetStyle(styleName);
    DcefBrowser1->Visible = true;
	//Check the menu item
	menuItem->Checked = (TStyleManager::ActiveStyle->Name == styleName) ? true : false;

	//Write to registry
	gApplicationStyle = stdstr(styleName);
	writeStringToRegistry(gApplicationRegistryRoot, "", "Theme", gApplicationStyle);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mBrowseForCacheFolderClick(TObject *Sender)
{
	//Browse for folder
	string res = browseForFolder(mImageCacheFolderE->getValue());
    if(folderExists(res))
    {
		mImageCacheFolderE->setValue(res);
    }
    else
    {
    	Log(lWarning) << "Cache folder was not set..";
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mCLearMemoClick(TObject *Sender)
{
	infoMemo->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CopyValidZs1Click(TObject *Sender)
{
	//Figure out wich listbox called
	TCheckListBox* lb = dynamic_cast<TCheckListBox*>(ZsPopUpMenu->PopupComponent);

    if(!lb)
    {
    	return;
    }

    stringstream zs;
    for(int i = 0; i < lb->Count; i++)
    {
    	zs << stdstr(lb->Items->Strings[i]);
        if(i < (lb->Count -1))
        {
        	zs <<",";
        }
    }
	sendToClipBoard(zs.str());
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mCloseBottomPanelBtnClick(TObject *Sender)
{
	mBottomPanel->Visible = false;
    mShowBottomPanelBtn->Top = StatusBar1->Top - 1;
    Splitter2->Visible = false;
    mShowBottomPanelBtn->Visible = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mShowBottomPanelBtnClick(TObject *Sender)
{
	mBottomPanel->Visible = true;
    Splitter2->Visible = true;
    mShowBottomPanelBtn->Visible = false;
    Splitter2->Top = mBottomPanel->Top - 1;
    StatusBar1->Top = mBottomPanel->Top + mBottomPanel->Height + 1;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ParseNDVIZURL1Click(TObject *Sender)
{
	Log(lInfo) << "Parsing clip board data";
	string cb = getClipBoardText();
    Log(lInfo) <<"ClipBoard: "<<cb;
    StringList url(cb, '{');
    //Structure of ndviz URL
	//http://ibs-forrestc-ux1.corp.alleninstitute.org:8001/#!
    //{
    //	'layers':
    //	{
    //		'ACQGephyrin':
	//		{
    //			'type':'image'_'source':'render://http://ibs-forrestc-ux1.corp.alleninstitute.org/Forrest/H16_03_005_HSV_HEF1AG65_R2An15dTom/ACQGephyrin'_'max':0.15259
    //		}
    //	}
    //_'navigation':
    //	{
    //		'pose':
    //		{
    //			'position':
    //			{
    //				'voxelSize':[1_1_1]_'voxelCoordinates':[4341.58935546875_680.30517578125_2]
    //			}
    //		}
    //	_'zoomFactor':1.8876945060824133
    //	}
    //}

    if(url.size() < 5)
    {
	   	Log(lError) <<"Failed to parse render URL.";
        return;
    }

    // '
    //	type
    //'
    //:
    //'
    //image
    //'
    //_
    //'
    //source
    //'
    //:
    //'
    //render://http://ibs-forrestc-ux1.corp.alleninstitute.org/Forrest/H16_03_005_HSV_HEF1AG65_R2An15dTom/ACQGephyrin
    //
    //'
    //_
    //'
    //max
    //'
    //:0.15259}}_
    //'
    //navigation
    //':
	//Now extract line with 'render'
    //Extract line with render URL
    string rurl1 = url.getLineContaining("render");
    if(!rurl1.size())
    {
    	Log(lError) <<"Failed to parse render URL";
        return;
    }

	Log(lInfo) <<rurl1;

    //Cut string on '\''
    StringList url_items(rurl1, '\'');

	Log(lInfo) <<url_items.getLineContaining("render");
	StringList pass3(url_items.getLineContaining("render"), '/');

    Log(lInfo) << "Pass3" << pass3;
	//Element 5,6 and 7 are owner, project and stack
    if(url_items.size() < 8)
    {
    	Log(lError) <<"Failed to parse render URL";
        return;
    }
    string owner(pass3[5]);
    string project(pass3[6]);
    string stack(pass3[7]);

    Log(lInfo) <<"Owner: "<<owner;
    Log(lInfo) <<"Project: "<<project;
    Log(lInfo) <<"Stack: "<<stack;

	//Now get z, x,y and zoom factor
    //				'voxelSize':[1_1_1]_'voxelCoordinates':[4341.58935546875_680.30517578125_2]
    string rurl2 = url.getLineContaining("voxel");
    if(rurl2.size() == 0)
    {
    	Log(lError) <<"Failed to parse render URL";
        return;
    }

    StringList pass4(rurl2, '[');
    Log(lDebug) << pass4;
    if(pass4.size() < 3)
    {
    	Log(lError) <<"Failed to parse render URL";
        return;
    }
    string nrs(pass4[2]);
    Log(lDebug) << nrs;
    StringList pass5(nrs, '_');
	Log(lDebug) << pass5;
    double x = toDouble(pass5[0]);
    double y = toDouble(pass5[1]);
    int z = toInt(pass5[2]);
    Log(lDebug) << "x = "<<x <<", y = "<<y<<", z = "<<z;
    //Zoomfactor
    StringList pass6(pass5[3], ':');
    Log(lDebug) << pass6;
    double zf = toDouble(pass6[1]);
    Log(lDebug) << "ZoomFactor: "<<zf;

    //Assume we got proper numbers, populate application
    int i = OwnerCB->Items->IndexOf(owner.c_str());
    if(i < 0)
    {
    	Log(lError) <<"Failed to parse render URL";
        return;
    }

	OwnerCB->ItemIndex = i;
    OwnerCB->OnChange(NULL);
    i = ProjectCB->Items->IndexOf(project.c_str());
    if(i < 0)
    {
    	Log(lError) <<"Failed to parse render URL";
        return;
    }

	ProjectCB->ItemIndex = i;
    ProjectCB->OnChange(NULL);

    i = StackCB->Items->IndexOf(stack.c_str());
    if(i < 0)
    {
    	Log(lError) <<"Failed to parse render URL";
        return;
    }

	StackCB->ItemIndex = i;
    StackCB->OnChange(NULL);

    XCoord->setValue(x);
    YCoord->setValue(y);

    i = mZs->Items->IndexOf(dsl::toString(z).c_str());
    if(i < 0)
    {
    	Log(lError) <<"Failed to parse render URL";
        return;
    }
	mZs->ItemIndex = i;
    mZs->Selected[i] = true;
    mZs->OnClick(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CreateNDVIZURL1Click(TObject *Sender)
{
    string url(createNDVIZURL());
    Log(lInfo) << url;
}

string TMainForm::createNDVIZURL()
{
	string URL("http://ibs-forrestc-ux1.corp.alleninstitute.org:8001/#!{'layers':{'STACK':{'type':'image'_'source':'render://http://ibs-forrestc-ux1.corp.alleninstitute.org/OWNER/PROJECT/STACK'_'max':MAX_INTENSITY}}_'navigation':{'pose':{'position':{'voxelSize':[1_1_1]_'voxelCoordinates':[X_CENTER_Y_CENTER_Z_VALUE]}}_'zoomFactor':ZOOM_FACTOR}}");
    Log(lInfo) << URL;

    double xCenter = XCoord->getValue() + Width->getValue()/2.;
	double yCenter = YCoord->getValue() + Height->getValue()/2.;
    URL = replaceSubstring("STACK", 	        stdstr(StackCB->Text), 	                                URL);
    URL = replaceSubstring("OWNER", 	        stdstr(OwnerCB->Text), 	                                URL);
    URL = replaceSubstring("PROJECT", 	        stdstr(ProjectCB->Text), 	                                URL);
    URL = replaceSubstring("MAX_INTENSITY", 	dsl::toString(2.0 * (MaxIntensity->getValue()/65535.0)), 	URL);
    URL = replaceSubstring("X_CENTER", 			dsl::toString(xCenter), 					                URL);
    URL = replaceSubstring("Y_CENTER", 			dsl::toString(yCenter), 					                URL);
    URL = replaceSubstring("Z_VALUE", 			dsl::toString(getCurrentZ()), 	 			                URL);
    URL = replaceSubstring("ZOOM_FACTOR", 		dsl::toString(0.5*(1.0/mScaleE->getValue())), 	 			URL);
	return URL;
}

void __fastcall TMainForm::OpenInNDVIZBtnClick(TObject *Sender)
{
	TButton* b = dynamic_cast<TButton*>(Sender);

    if(b == OpenInNDVIZBtn)
    {
	    string   url(createNDVIZURL());
		//ShellExecuteA(0,0, "chrome.exe", url.c_str(),0,SW_SHOWMAXIMIZED);
        DcefBrowser1->Load(url.c_str());
		return;
    }

    if(b == OpenFromNDVIZBtn)
    {
		ParseNDVIZURL1Click(NULL);
		return;
    }
}



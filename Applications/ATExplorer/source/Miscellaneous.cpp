#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "ATExplorerUIProperties.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------

using namespace dsl;
using namespace at;
extern ATExplorerUIProperties gUIProperties;
//---------------------------------------------------------------------------
void __fastcall TMainForm::About1Click(TObject *Sender)
{
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

//    DcefBrowser1->Visible = false;
	TReplaceFlags rFlags(rfIgnoreCase|rfReplaceAll);
	String styleName = StringReplace(menuItem->Caption, "&", "", rFlags);
	TStyleManager::SetStyle(styleName);
//    DcefBrowser1->Visible = true;

	//Check the menu item
	menuItem->Checked = (TStyleManager::ActiveStyle->Name == styleName) ? true : false;

	//Write to registry
	gUIProperties.AppTheme = stdstr(styleName);
	writeStringToRegistry(gUIProperties.AppRegistryRoot, "", "Theme", gUIProperties.AppTheme);
}

////---------------------------------------------------------------------------
//void __fastcall TMainForm::ParseNDVIZURL1Click(TObject *Sender)
//{
//	Log(lInfo) << "Parsing clip board data";
//	string cb = getClipBoardText();
//    Log(lInfo) <<"ClipBoard: "<<cb;
//    StringList url(cb, '{');
//    //Structure of ndviz URL
//	//http://ibs-forrestc-ux1.corp.alleninstitute.org:8001/#!
//    //{
//    //	'layers':
//    //	{
//    //		'ACQGephyrin':
//	//		{
//    //			'type':'image'_'source':'render://http://ibs-forrestc-ux1.corp.alleninstitute.org/Forrest/H16_03_005_HSV_HEF1AG65_R2An15dTom/ACQGephyrin'_'max':0.15259
//    //		}
//    //	}
//    //_'navigation':
//    //	{
//    //		'pose':
//    //		{
//    //			'position':
//    //			{
//    //				'voxelSize':[1_1_1]_'voxelCoordinates':[4341.58935546875_680.30517578125_2]
//    //			}
//    //		}
//    //	_'zoomFactor':1.8876945060824133
//    //	}
//    //}
//
//    if(url.size() < 5)
//    {
//	   	Log(lError) <<"Failed to parse render URL.";
//        return;
//    }
//
//    // '
//    //	type
//    //'
//    //:
//    //'
//    //image
//    //'
//    //_
//    //'
//    //source
//    //'
//    //:
//    //'
//    //render://http://ibs-forrestc-ux1.corp.alleninstitute.org/Forrest/H16_03_005_HSV_HEF1AG65_R2An15dTom/ACQGephyrin
//    //
//    //'
//    //_
//    //'
//    //max
//    //'
//    //:0.15259}}_
//    //'
//    //navigation
//    //':
//	//Now extract line with 'render'
//    //Extract line with render URL
//    string rurl1 = url.getLineContaining("render");
//    if(!rurl1.size())
//    {
//    	Log(lError) <<"Failed to parse render URL";
//        return;
//    }
//
//	Log(lInfo) <<rurl1;
//
//    //Cut string on '\''
//    StringList url_items(rurl1, '\'');
//
//	Log(lInfo) <<url_items.getLineContaining("render");
//	StringList pass3(url_items.getLineContaining("render"), '/');
//
//    Log(lInfo) << "Pass3" << pass3;
//	//Element 5,6 and 7 are owner, project and stack
//    if(url_items.size() < 8)
//    {
//    	Log(lError) <<"Failed to parse render URL";
//        return;
//    }
//    string owner(pass3[5]);
//    string project(pass3[6]);
//    string stack(pass3[7]);
//
//    Log(lInfo) <<"Owner: "<<owner;
//    Log(lInfo) <<"Project: "<<project;
//    Log(lInfo) <<"Stack: "<<stack;
//
//	//Now get z, x,y and zoom factor
//    //				'voxelSize':[1_1_1]_'voxelCoordinates':[4341.58935546875_680.30517578125_2]
//    string rurl2 = url.getLineContaining("voxel");
//    if(rurl2.size() == 0)
//    {
//    	Log(lError) <<"Failed to parse render URL";
//        return;
//    }
//
//    StringList pass4(rurl2, '[');
//    Log(lDebug) << pass4;
//    if(pass4.size() < 3)
//    {
//    	Log(lError) <<"Failed to parse render URL";
//        return;
//    }
//    string nrs(pass4[2]);
//    Log(lDebug) << nrs;
//    StringList pass5(nrs, '_');
//	Log(lDebug) << pass5;
//    double x = toDouble(pass5[0]);
//    double y = toDouble(pass5[1]);
//    int z = toInt(pass5[2]);
//    Log(lDebug) << "x = "<<x <<", y = "<<y<<", z = "<<z;
//    //Zoomfactor
//    StringList pass6(pass5[3], ':');
//    Log(lDebug) << pass6;
//    double zf = toDouble(pass6[1]);
//    Log(lDebug) << "ZoomFactor: "<<zf;
//
//    //Assume we got proper numbers, populate application
//    int i = OwnerCB->Items->IndexOf(owner.c_str());
//    if(i < 0)
//    {
//    	Log(lError) <<"Failed to parse render URL";
//        return;
//    }
//
//	OwnerCB->ItemIndex = i;
//    OwnerCB->OnChange(NULL);
//    i = ProjectCB->Items->IndexOf(project.c_str());
//    if(i < 0)
//    {
//    	Log(lError) <<"Failed to parse render URL";
//        return;
//    }
//
//	ProjectCB->ItemIndex = i;
//    ProjectCB->OnChange(NULL);
//
//    i = StackCB->Items->IndexOf(stack.c_str());
//    if(i < 0)
//    {
//    	Log(lError) <<"Failed to parse render URL";
//        return;
//    }
//
//	StackCB->ItemIndex = i;
//    StackCB->OnChange(NULL);
//
//    XCoordE->setValue(x);
//    YCoordE->setValue(y);
//
//    i = mZs->Items->IndexOf(dsl::toString(z).c_str());
//    if(i < 0)
//    {
//    	Log(lError) <<"Failed to parse render URL";
//        return;
//    }
//	mZs->ItemIndex = i;
//    mZs->Selected[i] = true;
//    mZs->OnClick(NULL);
//}
//

//---------------------------------------------------------------------------
void __fastcall TMainForm::ToggleBottomPanelAExecute(TObject *Sender)
{
    if(BottomPanel->Visible)
    {
        BottomPanel->Visible = false;
        ShowBottomPanelBtn->Top = StatusBar1->Top - 1;
        Splitter2->Visible = false;
        ShowBottomPanelBtn->Visible = true;

    }
    else
    {
        BottomPanel->Visible = true;
        Splitter2->Visible = true;
        ShowBottomPanelBtn->Visible = false;
        Splitter2->Top = BottomPanel->Top - 1;
        StatusBar1->Top = BottomPanel->Top + BottomPanel->Height + 1;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ToggleBottomPanelAUpdate(TObject *Sender)
{
	ToggleBottomPanelA->Caption = (BottomPanel->Visible) ? "Hide Bottom Panel" : "Show Bottom Panel";

	if(!BottomPanel->Visible)
    {
        ShowBottomPanelBtn->Caption = "^";
    }
}

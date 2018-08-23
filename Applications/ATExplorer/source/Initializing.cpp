#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "ateAppUtilities.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------

using namespace dsl;
extern at::AppUtilities gAU;


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    if(mIsStyleMenuPopulated == false)
    {
        populateStyleMenu(ThemesMenu, ThemesMenuClick);
        mIsStyleMenuPopulated = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	this->Caption = vclstr(createWindowTitle("ATExplorer", Application));
    this->DoubleBuffered = true;

	gLogger.setLogLevel(gAU.LogLevel);
    TLogMemoFrame1->init();

//    mCurrentROI.setX1(XCoordE->getValue());
//    mCurrentROI.setY1(YCoordE->getValue());
//    mCurrentROI.setWidth(Width->getValue());
//    mCurrentROI.setHeight(Height->getValue());
//
//    //Setup renderclient
//    mRC.setBaseURL(BaseURLE->getValue());
//    mRC.getProject().init(gAU.CurrentOwner.getValue(), gAU.CurrentProject.getValue(), gAU.CurrentStack.getValue());
//
//    //Populate owners
//    StringList o = mRC.getOwners();
//    if(o.size())
//    {
//		populateDropDown(o, OwnerCB);
//    }
//
//	//Select owner
//    int index = OwnerCB->Items->IndexOf(gAU.CurrentOwner.c_str());
//
//    if(index > -1)
//    {
//		OwnerCB->ItemIndex = index;
//        OwnerCB->OnChange(NULL);
//
//        //Select last project
//        index = ProjectCB->Items->IndexOf(gAU.CurrentProject.c_str());
//        if(index > -1)
//        {
//            ProjectCB->ItemIndex = index;
//            ProjectCB->OnChange(NULL);
//
//            //Then select last stack
//            index = StackCB->Items->IndexOf(gAU.CurrentStack.c_str());
//            if(index > -1)
//            {
//                StackCB->ItemIndex = index;
//                StackCB->OnChange(NULL);
//            }
//        }
//    }
//
//	enableDisableGroupBox(TestSSHGB, 		false);
//	enableDisableGroupBox(StackGenerationGB,false);
//
//    //Setup path for ssh
//	TSSHFrame1->ScFileStorage->Path = vclstr(gAU.AppDataFolder);
//    if(gAU.ConnectSSHServersOnStartup)
//    {
//		TSSHFrame1->ConnectBtnClick(Sender);
//    }
}

bool TMainForm::setupAndReadIniParameters()
{
	//Setup parameters
    gAU.setupIniParameters();
	gAU.GeneralProperties->read();

//    gAU.GeneralProperties->add((BaseProperty*)  &RenderPort->getProperty()->setup(	        "RENDER_PORT", 	                    8988));

    //These will be part of last loaded project
//    gAU.GeneralProperties->add((BaseProperty*)  &mScaleE->getProperty()->setup(		    	"SCALE", 			                0.02));
//    gAU.GeneralProperties->add((BaseProperty*)  &XCoordE->getProperty()->setup(	        	"VIEW_X_COORD",    	                0));
//    gAU.GeneralProperties->add((BaseProperty*)  &YCoordE->getProperty()->setup(	        	"VIEW_Y_COORD",    	                0));
//    gAU.GeneralProperties->add((BaseProperty*)  &Width->getProperty()->setup(		        "VIEW_WIDTH", 		                1000));
//    gAU.GeneralProperties->add((BaseProperty*)  &Height->getProperty()->setup(	        	"VIEW_HEIGHT", 		                1000));
//    gAU.GeneralProperties->add((BaseProperty*)  &MinIntensityE->getProperty()->setup(	    "MIN_INTENSITY", 		            0));
//    gAU.GeneralProperties->add((BaseProperty*)  &MaxIntensityE->getProperty()->setup(	    "MAX_INTENSITY", 		            65535));
//
//    //Stack Generation
//	gAU.GeneralProperties->add((BaseProperty*)  &VolumesFolder->getProperty()->setup(		"VOLUMES_ROOT_FOLDER",  	  		"/nas1/temp"));
//	gAU.GeneralProperties->add((BaseProperty*)  &SubFolder1->getProperty()->setup(			"VOLUMES_SUB_FOLDER_1",  	  		"temp"));
//	gAU.GeneralProperties->add((BaseProperty*)  &VolumesScaleE->getProperty()->setup(	   	"VOLUMES_SCALE",  	 		 		0.01));

	//Read from file. Create if file do not exist

//	BaseURLE->assignExternalProperty(&gAU.BaseURL, true);
//
//	//Update UI
//    RenderPort->update();
//    mScaleE->update();
//    XCoordE->update();
//    YCoordE->update();
//    Width->update();
//    Height->update();
//	MinIntensityE->update();
//	MaxIntensityE->update();
//    VolumesFolder->update();
//    SubFolder1->update();
//    VolumesScaleE->update();

//    gAU.ServerProperties->add((BaseProperty*)  &TSSHFrame1->edSSHHost->getProperty()->setup("REMOTE_HOST", 	                  	"atbigdawg"));
//    gAU.ServerProperties->add((BaseProperty*)  &TSSHFrame1->seSSHPort->getProperty()->setup("REMOTE_PORT", 	                  	22));
//    gAU.ServerProperties->add((BaseProperty*)  &TSSHFrame1->edSSHUserName->getProperty()->setup("REMOTE_USER_NAME", 	       	"albert"));
//    gAU.ServerProperties->add((BaseProperty*)  &TSSHFrame1->edSSHPassword->getProperty()->setup("REMOTE_USER_PASSWORD",        	"123"));
//
//	gAU.ServerProperties->read();

//	TSSHFrame1->edSSHHost->update();
//    TSSHFrame1->seSSHPort->update();
//    TSSHFrame1->edSSHUserName->update();
//    TSSHFrame1->edSSHPassword->update();

	BottomPanel->Height = gAU.BottomPanelHeight;
//	mRC.setLocalCacheFolder(gAU.LocalCacheFolder.getValue());
    return true;
}


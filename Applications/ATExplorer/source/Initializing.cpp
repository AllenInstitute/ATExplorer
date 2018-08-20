#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "ateAppUtilities.h"
//---------------------------------------------------------------------------

using namespace dsl;
extern at::AppUtilities gAU;
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	this->Caption = vclstr(createWindowTitle("ATExplorer", Application));
    this->DoubleBuffered = true;

	gLogger.setLogLevel(mLogLevel);
    TLogMemoFrame1->init();

    mCurrentROI.setX1(XCoordE->getValue());
    mCurrentROI.setY1(YCoordE->getValue());
    mCurrentROI.setWidth(Width->getValue());
    mCurrentROI.setHeight(Height->getValue());

    //Setup renderclient
    mRC.setBaseURL(BaseURLE->getValue());
    mRC.getProject().init(mCurrentOwner.getValue(), mCurrentProject.getValue(), mCurrentStack.getValue());

    //Populate owners
    StringList o = mRC.getOwners();
    if(o.size())
    {
		populateDropDown(o, OwnerCB);
    }

	//Select owner
    int index = OwnerCB->Items->IndexOf(mCurrentOwner.c_str());

    if(index > -1)
    {
		OwnerCB->ItemIndex = index;
        OwnerCB->OnChange(NULL);

        //Select last project
        index = ProjectCB->Items->IndexOf(mCurrentProject.c_str());
        if(index > -1)
        {
            ProjectCB->ItemIndex = index;
            ProjectCB->OnChange(NULL);

            //Then select last stack
            index = StackCB->Items->IndexOf(mCurrentStack.c_str());
            if(index > -1)
            {
                StackCB->ItemIndex = index;
                StackCB->OnChange(NULL);
            }
        }
    }

	enableDisableGroupBox(TestSSHGB, 		false);
	enableDisableGroupBox(StackGenerationGB,false);

    //Setup path for ssh
	TSSHFrame1->ScFileStorage->Path = vclstr(gAU.AppDataFolder);
	TSSHFrame1->ConnectBtnClick(Sender);
}

bool TMainForm::setupAndReadIniParameters()
{
	mGeneralProperties->setIniFile(&gAU.getIniFile());

	//Setup parameters
	mGeneralProperties->setSection("GENERAL");
	mGeneralProperties->add((BaseProperty*)  &mBottomPanelHeight.setup( 	            "HEIGHT_OF_BOTTOM_PANEL",    	    205));
	mGeneralProperties->add((BaseProperty*)  &mLogLevel.setup( 	                    	"LOG_LEVEL",    	                lAny));

    mGeneralProperties->add((BaseProperty*)  &BaseURLE->getProperty()->setup(	        "BASE_URL", 	                    "http://ibs-forrestc-ux1.corp.alleninstitute.org"));
    mGeneralProperties->add((BaseProperty*)  &RenderPort->getProperty()->setup(	        "RENDER_PORT", 	                    8988));

    mGeneralProperties->add((BaseProperty*)  &mCurrentOwner.setup(		        		"OWNER", 		                    "Sharmishtaas"));
    mGeneralProperties->add((BaseProperty*)  &mCurrentProject.setup(	    			"PROJECT", 		                    "M270907_Scnn1aTg2Tdt_13"));
    mGeneralProperties->add((BaseProperty*)  &mCurrentStack.setup(	        			"STACK_NAME", 	                    "ALIGNEDSTACK_DEC12"));

    mGeneralProperties->add((BaseProperty*)  &mScaleE->getProperty()->setup(		    "SCALE", 			                0.02));
    mGeneralProperties->add((BaseProperty*)  &XCoordE->getProperty()->setup(	        "VIEW_X_COORD",    	                0));
    mGeneralProperties->add((BaseProperty*)  &YCoordE->getProperty()->setup(	        "VIEW_Y_COORD",    	                0));
    mGeneralProperties->add((BaseProperty*)  &Width->getProperty()->setup(		        "VIEW_WIDTH", 		                0));
    mGeneralProperties->add((BaseProperty*)  &Height->getProperty()->setup(	        	"VIEW_HEIGHT", 		                0));
    mGeneralProperties->add((BaseProperty*)  &MinIntensityE->getProperty()->setup(	    "MIN_INTENSITY", 		            0));
    mGeneralProperties->add((BaseProperty*)  &MaxIntensityE->getProperty()->setup(	    "MAX_INTENSITY", 		            65535));

	mGeneralProperties->add((BaseProperty*)  &ImageCacheFolderE->getProperty()->setup(	"IMAGE_CACHE_FOLDER",  				"C:\\ImageCache"));

    //Stack Generation
	mGeneralProperties->add((BaseProperty*)  &VolumesFolder->getProperty()->setup(		"VOLUMES_ROOT_FOLDER",  	  		"/nas1/temp"));
	mGeneralProperties->add((BaseProperty*)  &SubFolder1->getProperty()->setup(			"VOLUMES_SUB_FOLDER_1",  	  		"temp"));
	mGeneralProperties->add((BaseProperty*)  &VolumesScaleE->getProperty()->setup(	   	"VOLUMES_SCALE",  	 		 		0.01));

	//Read from file. Create if file do not exist
	mGeneralProperties->read();

    //For convenience and for option form, populate appProperties container
	gAU.append(mGeneralProperties);

	//Update UI
    BaseURLE->update();
    RenderPort->update();
    mScaleE->update();
    XCoordE->update();
    YCoordE->update();
    Width->update();
    Height->update();
	MinIntensityE->update();
	MaxIntensityE->update();
	ImageCacheFolderE->update();
    VolumesFolder->update();
    SubFolder1->update();
    VolumesScaleE->update();

	//Remote server properties
	mServer1Properties->setIniFile(&gAU.getIniFile());
    mServer1Properties->setSection("REMOTE_SERVER_1");
    mServer1Properties->add((BaseProperty*)  &TSSHFrame1->edSSHHost->getProperty()->setup("REMOTE_HOST", 	                  	"atbigdawg"));
    mServer1Properties->add((BaseProperty*)  &TSSHFrame1->seSSHPort->getProperty()->setup("REMOTE_PORT", 	                  	22));
    mServer1Properties->add((BaseProperty*)  &TSSHFrame1->edSSHUserName->getProperty()->setup("REMOTE_USER_NAME", 	       	"albert"));
    mServer1Properties->add((BaseProperty*)  &TSSHFrame1->edSSHPassword->getProperty()->setup("REMOTE_USER_PASSWORD",        	"123"));

	mServer1Properties->read();

	TSSHFrame1->edSSHHost->update();
    TSSHFrame1->seSSHPort->update();
    TSSHFrame1->edSSHUserName->update();
    TSSHFrame1->edSSHPassword->update();

	BottomPanel->Height = mBottomPanelHeight;
	mRC.setLocalCacheFolder(ImageCacheFolderE->getValue());
    return true;
}


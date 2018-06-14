#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "atSSHUtils.h"

using namespace dsl;


void __fastcall TMainForm::TSSHFrame1ScSSHShell1AsyncReceive(TObject *Sender)
{
	//Parse messages from the server
    string line(stdstr(TSSHFrame1->ScSSHShell1->ReadString()));
	if(contains("mxplutx",line))
    {
		Log(lInfo) << "Finished one stack...";
    }
    else
    {
 		Log(lDebug) << line;
    }
}

void __fastcall TMainForm::CMDButtonClick(TObject *Sender)
{
	stringstream cmd;
    cmd << stdstr(mCMD->Text) << endl;
    TSSHFrame1->ScSSHShell1->WriteString(vclstr(cmd.str()));
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::RunClick(TObject *Sender)
{
	//Create remote jobs by script
    string scriptName("runner.sh");

    //Create empty, runnable script on server
	string remoteScriptName = createEmptyScriptFileOnServer(scriptName);

	//Populate remote script
	if(!populateRemoteScript(remoteScriptName))
    {
    	Log(lError) << "Failed to populate remote script.. bailing";
    	return;
    }

    //Create command lines (jobs)
   	vector<string> commands;
    StringList stacks = getCheckedItems(StacksForProjectCB);
	for(int i = 0; i < stacks.size() ; i++)
    {
		commands.push_back(createRemoteCommand(remoteScriptName, stacks[i]));
        Log(lDebug) << "Command "<<i<<" :"<<commands[i];
    }

	for(int i = 0; i < commands.size(); i++)
    {
    	runJob(commands[i]);
    }
}

string TMainForm::createEmptyScriptFileOnServer(const string& scriptName)
{
    stringstream cmd;
	//First create remote folders
    string folders(joinPath(stdstr(VolumesFolder->Text), stdstr(SubFolder1->Text), '/'));
    cmd << "mkdir -p "<<folders;

    string remoteScript(joinPath(folders, scriptName, '/'));

	cmd << " && touch "<< remoteScript << endl;
    TSSHFrame1->ScSSHShell1->WriteString(vclstr(cmd.str()));
	cmd.str("");

    //Make executable
	cmd << "chmod +x "<< remoteScript << endl;
    TSSHFrame1->ScSSHShell1->WriteString(vclstr(cmd.str()));
	return remoteScript;
}

bool TMainForm::populateRemoteScript(const string& remoteScriptName)
{
    stringstream cmd;
    StringList lines(getStrings(BashScriptMemo));
    if(lines.size() <= 1)
    {
    	Log(lError) << "Can't populate remote script. Script Memo is Empty??";
        return false;
    }

	cmd << "echo \"\" > " <<remoteScriptName << endl;
    //Copy content of memo
    for(int i = 0 ; i < lines.size(); i++)
    {
		//Log(lInfo) << "echo "<<escape(lines[i])<< " >> " << remoteScript << endl;
		cmd << "echo "<< ssh_escape(lines[i])<< " >> " << remoteScriptName << endl;
    }

    TSSHFrame1->ScSSHShell1->WriteString(vclstr(cmd.str()));
    cmd.str("");
    return true;
}

void TMainForm::runJob(const string& job)
{
    TSSHFrame1->ScSSHShell1->WriteString(vclstr(job));
}

string TMainForm::createRemoteCommand(const string& remoteScript, const string& stack)
{
	stringstream cmd;

	//Create commandline for remote bash script
	cmd << remoteScript;

    //First argument is number of sections
    cmd<<" "<<getNumberOfCheckedItems(mZs);

    //Second argument is section numbers
    cmd << " '";
	for(int i = 0; i < mZs->Count; i++)
    {
    	if(mZs->Checked[i] == true)
        {
            cmd << mZs->Items->Strings[i].ToInt();
            if(i < mZs->Count -1)
            {
                cmd << " ";
            }
        }
    }
    cmd <<"'";

    //Third argument is root outputfolder
    cmd <<" "<<stdstr(VolumesFolder->Text);

    //Fourth arg is custom outputfolder
	cmd <<" "<<stdstr(SubFolder1->Text);

    //Fifth arg is custom outputfolder
	cmd <<" "<<stack;

	//Sixth is owner
    cmd <<" "<<mCurrentOwner;

    //7th - project
    cmd <<" "<<mCurrentProject;

    //8th - scale
	cmd <<" "<<stdstr(VolumesScaleE->Text);

	//9th - static bounds?
    cmd <<" "<<dsl::toString(CreateTIFFStackCB->Checked);

 	//10th - delete individual tiffs?
    if(CreateTIFFStackCB->Checked)
    {
    	cmd <<" "<<dsl::toString(DeleteTempTiffsCB->Checked);
    }
    else
    {
    	cmd <<" false";
    }

    //11th - Z batch size
    cmd <<" "<<ZBatchSizeE->getValue();

    //12th - Max jobs size
	cmd <<" "<<MaxNumberOfRemoteJobsE->getValue();

    //13th - Job niceness
	cmd <<" "<<NicenessE->getValue();

    //14th - imageType
	cmd <<" "<<toInt(stdstr(ImageTypeCB->Text));

    //15th - pad file names
	cmd <<" "<<dsl::toString(PadFileNamesWithZeroesCB->Checked);

	//16th - static bounds?
    cmd <<" "<<dsl::toString(BoundsCB->Checked);

    if(BoundsCB->Checked)
    {
    	//Pass bounds, xmin, xmax, ymin,ymax
        cmd <<" '"
        	<<XCoord->getValue()<<","
        	<<XCoord->getValue() + Width->getValue()<<","
            <<YCoord->getValue()<<","
            <<YCoord->getValue() + Height->getValue()<<"'";
    }
    else
    {
    	//Pass bounds, xmin, xmax, ymin,ymax
        cmd <<" '"
        	<<0<<","
        	<<0<<","
            <<0<<","
            <<0<<"'";
    }

    cmd << " &" ;
    cmd << endl;

	return cmd.str();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::TSSHFrame1ScSSHClientAfterConnect(TObject *Sender)
{
	enableDisableGroupBox(StackGenerationGB, true);
	enableDisableGroupBox(TestSSHGB, true);

  	TSSHFrame1->ScSSHClientAfterConnect(Sender);
	DeleteTempTiffsCB->Enabled = CreateTIFFStackCB->Checked;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::TSSHFrame1ScSSHClientAfterDisconnect(TObject *Sender)
{
	TSSHFrame1->ScSSHClientAfterDisconnect(Sender);
	enableDisableGroupBox(StackGenerationGB, false);
	enableDisableGroupBox(TestSSHGB, false);
}


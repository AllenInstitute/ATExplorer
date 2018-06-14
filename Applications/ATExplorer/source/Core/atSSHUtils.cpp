#pragma hdrstop
#include "atSSHUtils.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include <sstream>
#include "ScSSHChannel.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace dsl;


string createEmptyScriptFileOnServer(TScSSHShell* ssh, const string& subFolders, const string& scriptName)
{
    stringstream cmd;

	//First create remote folders
    cmd << "mkdir -p "<<subFolders;

    string remoteScript(joinPath(subFolders, scriptName, '/'));

	cmd << " && touch "<< remoteScript << endl;
    ssh->WriteString(vclstr(cmd.str()));
	cmd.str("");

    //Make executable
	cmd << "chmod +x "<< remoteScript << endl;
    ssh->WriteString(vclstr(cmd.str()));
	return remoteScript;
}

bool populateRemoteScript(TScSSHShell* ssh, const string& remoteScriptName, const StringList& lines)
{
    stringstream cmd;
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

    ssh->WriteString(vclstr(cmd.str()));
    cmd.str("");
    return true;
}

string ssh_escape(const string& before)
{
    string escaped(before);
    //Pretty bisarre syntax.. see http://stackoverflow.com/questions/1250079/how-to-escape-single-quotes-within-single-quoted-strings
    escaped = replaceSubstring("'", "'\"'\"'", escaped);
    return "'" + escaped + "'";
}

void runRemoteJob(TScSSHShell* ssh, const string& job)
{
    ssh->WriteString(vclstr(job));
}

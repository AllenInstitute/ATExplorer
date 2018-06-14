#ifndef atSSHUtilsH
#define atSSHUtilsH
#include <string>
#include "dslStringList.h"
//---------------------------------------------------------------------------

using dsl::StringList;
using std::string;

namespace Scsshchannel
{
	class TScSSHShell;
}

using Scsshchannel::TScSSHShell;

//!Escape lines
string ssh_escape(const string& before);

//!Create an empty file on the server
string 	createEmptyScriptFileOnServer(TScSSHShell * ssh, const string& subFolder, const string& fName);

//!Populate remote script with content
bool 	populateRemoteScript(TScSSHShell* ssh, const string& remoteScriptName, const StringList& lines);

//!Start remote job, over ssh
void   runRemoteJob(TScSSHShell* ssh, const string& job);

#endif

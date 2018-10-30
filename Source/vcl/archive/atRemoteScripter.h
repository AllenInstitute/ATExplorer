#ifndef atRemoteScripterH
#define atRemoteScripterH
#include "atExplorerObject.h"
#include "ScSSHChannel.hpp"
#include "dslStringList.h"
#include <string>

//---------------------------------------------------------------------------

//!Class that sets up and run remote scripts through a ssh conenction
//!Remote script execution involve creataion of a full command string that
//!starts with a command, followed by a script name and script arguments
//!server response is captured in the mServerResponse container

using dsl::StringList;
using std::string;

//---------------------------------------------------------------------------
namespace at
{

using Scsshchannel::TScSSHShell;

class PACKAGE RemoteScripter : public ExplorerObject
{
    public:
                                            RemoteScripter(const string& scriptFileName, TScSSHShell* ssh = NULL);
                                            ~RemoteScripter();
        string 	                            createFullRemoteCommand();
        void	                            setRemoteCommand(const string& cmd);
        string                              getRemoteCommand();
        void                                useConnection(TScSSHShell* c);
        void                                addArgument(const string& argument);
        StringList                          getArguments();
        void                                run();
        void                                clearArguments();

    protected:
                                            //!The remote command is everyting before the actual script
        string                              mRemoteCommand;
        string                              mScriptName;
        StringList                          mArguments;
        StringList                          mServerResponse;

                                            //!The ssh connection
        TScSSHShell*						mSSHShell;
};

}
#endif

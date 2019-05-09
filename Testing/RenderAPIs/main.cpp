#pragma hdrstop
#pragma argsused
#include <IdHTTP.hpp>
#include "atRenderClient.h"
#include "atPointMatchCollection.h"
#include "atRenderProject.h"
#include "atRenderServiceParameters.h"
#include "dslLogger.h"
#include "dslStringUtils.h"

using namespace at;
using namespace dsl;

int main()
{
    try
    {
        //Create protocol object
        shared_ptr<Idhttp::TIdHTTP> httpC (new Idhttp::TIdHTTP());

        //RenderProject rp("TheProject", "ATExplorer", "TestData", "");
        RenderClient rc(httpC, "localhost");


        StringList owners = rc.StackDataAPI.getOwners();
        Log(lInfo) << owners;

        string owner("ATExplorer");
        string project("QT2");

        string result = rc.ServerConfigurationAPI.getServerProperties();
        Log(lInfo) << "Result:\n" << result;
//        //First string is filePath
//        if(list.size() == 2)
//        {
//            Log(lInfo) << "FilePath: " << list[0];
//
//            //Next are properties
//            string cleaned = stripCharacters(",{}\"", list[1]);
//            cleaned = trim(cleaned, '\n');
//            cleaned = replaceCharacter(':', '=', cleaned);
//
//            Log(lInfo) << "Properties: " << cleaned;
//        }
//        else
//        {
//            Log(lError) << "Bad response..";
//        }
    }
    catch(...)
    {
        Log(lError) << "Bad..";
    }

	return 0;
}

#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "dslFoundation")
#pragma comment(lib, "tinyxml2.lib")
#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "indyprotocols.bpi")
#pragma comment(lib, "vcl.bpi")
#pragma comment(lib, "rtl.bpi")

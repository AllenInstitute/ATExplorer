#pragma hdrstop
#pragma argsused
#include <IdHTTP.hpp>
#include "atRenderClient.h"
#include "atPointMatchCollection.h"
#include "atRenderProject.h"
#include "atRenderServiceParameters.h"
#include "dslLogger.h"

using namespace at;
using namespace dsl;

int main()
{
    try
    {
        unique_ptr<Idhttp::TIdHTTP> httpC (new Idhttp::TIdHTTP());
        RenderServiceParameters rsp("Dummy", "localhost");
        RenderProject rp("TheProject", "ATExplorer", "TestData", "");
        RenderClient rc(rp, httpC.get(), &rsp);
        PointMatchCollection collection("ATExplorer", "T4_lowres_round", &rc);

        StringList owners = rc.getOwners();
        Log(lInfo) << owners;

        if(collection.fetch())
        {
            StringList groups = collection.getGroupIDs();
            StringList pGroupIDS = collection.getPGroupIDs();
            StringList qGroupIDS = collection.getQGroupIDs();
            Log(lInfo) << "The collection has: " << collection.getCount() << " pairs";
            Log(lInfo) << "The collection has: " << groups.count() << " groups: " << groups;
            Log(lInfo) << "P group IDSs: " << pGroupIDS.count() << " groups: " << pGroupIDS;
            Log(lInfo) << "Q group IDSs: " << qGroupIDS.count() << " groups: " << qGroupIDS;

            List<PointMatch> list = collection.getPQMatches("4000", "4001");
        }
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

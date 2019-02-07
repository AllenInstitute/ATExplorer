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
        //Create protocol object
        shared_ptr<Idhttp::TIdHTTP> httpC (new Idhttp::TIdHTTP());

        //RenderProject rp("TheProject", "ATExplorer", "TestData", "");
        RenderClient rc(httpC, "localhost");

        StringList owners = rc.StackDataAPI.getOwners();
        Log(lInfo) << owners;

        string owner("ATExplorer");
        string project("QT2");
        StringList stacks = rc.StackDataAPI.getStacksForProject(owner, project);
        Log(lInfo) << "Stacks in project: " <<project << stacks;

        PointMatchCollection collection(owner, "TestReduced_3_HR_3D", &rc);

        if(collection.fetch())
        {
            StringList groups = collection.getGroupIDs();
            StringList pGroupIDS = collection.getPGroupIDs();
            StringList qGroupIDS = collection.getQGroupIDs();
            Log(lInfo) << "The collection has: " << collection.getCount() << " pairs";
            Log(lInfo) << "The collection has: " << groups.count() << " groups: " << groups;
            Log(lInfo) << "P group IDSs: " << pGroupIDS.count() << " groups: " << pGroupIDS;
            Log(lInfo) << "Q group IDSs: " << qGroupIDS.count() << " groups: " << qGroupIDS;
            ListOfObjects<PointMatch> list = collection.getPQMatches("4000", "4001");
        }

//        rc.PointMatchAPI.deletePointMatchCollection(owner, "TEST");
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

#pragma hdrstop
#include "atIFData.h"
#include "dslLogger.h"
#include "Poco/Glob.h"
#include <set>
//---------------------------------------------------------------------------

using namespace dsl;
using namespace std;
using namespace Poco;

ATIFData::ATIFData(const Path& p, bool val)
:
ATData(p)
{
    if(val)
    {
        validate();
    }
}

bool ATIFData::validate()
{
	Log(lDebug) << "Validating AT Data in folder: " << mBasePath.toString();

    //Check that root folder exists
    if(!mBasePath.isDirectory())
    {
        Log(lWarning) << mBasePath.toString() << " is not a valid ATData basepath";
        return false;
    }

    //Validate Ribbon folder in base folder
    for(int i = 0 ; i < getNumberOfRibbonFolders(); i++)
    {
	    //Could spawn some threads for this...

    }




    return true;
}

int ATIFData::getNumberOfRibbonFolders()
{
    //Check how many Ribbon folders that are present
    FileFolders fldrs = mBasePath.getSubFolders();
    int count(0);

	for(int i = 0; i < fldrs.size(); i++)
    {
        if(startsWith("Ribbon", fldrs[i]->toString()))
        {
            count++;
        }
    }
    return count;
}

FileFolder ATIFData::getRibbonFolder(int fldr)
{

}

#pragma hdrstop
#include "atIFData.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

using namespace dsl;

ATIFData::ATIFData(const Path& p)
:
ATData(p),
mRibbonFolders(p, NULL)
{}

bool ATIFData::validate()
{
    //Check that root folder exists
    if(!mBasePath.isDirectory())
    {
        Log(lWarning) << mBasePath.toString() << " is not a valid ATData basepath";
        return false;
    }
    return true;
}

int ATIFData::getNumberOfRibbons()
{
    //Check how many Ribbon folders that are present
    return -1;
}

FileFolder ATIFData::getRibbonFolder(int fldr)
{

}

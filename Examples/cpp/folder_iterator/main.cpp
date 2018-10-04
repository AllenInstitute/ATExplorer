#pragma hdrstop
#pragma argsused
#include "atFileFolder.h"
#include "dslLogger.h"

using namespace at;
using namespace dsl;
void listSubFolders(FileFolderSP ff);
int main()
{
    FileFolderSP folder;//(new FileFolder("F:\\data\\M33\\raw\\data"));

    for(int i = 0; i < 1000; i++)
    {
        if(folder)
        {
        	folder->reset();
        }
        if(!folder)
        {
            folder = FileFolderSP(new FileFolder("F:\\data\\M33\\raw\\data\\"));
        }

        gLogger.logToConsole(true);

        folder->scan();

//        FileFolders sf = folder->getSubFolders();
//
//        for(int i = 0; i < sf.count(); i++)
//        {
//             Log(lInfo) << sf[i]->toString();
//             if(sf[i]->getSubFolders().count())
//             {
//                listSubFolders(sf[i]);
//             }
//        }
    }

	return 0;
}


void listSubFolders(FileFolderSP ff)
{
    FileFolders sf = ff->getSubFolders();
    for(int i = 0; i < sf.count(); i++)
    {
        FileFolderSP sub = sf[i];
         Log(lInfo) << sub->toString();
         if(sf[i]->getSubFolders().count())
         {
            listSubFolders(sf[i]);
         }
    }
}

#pragma comment(lib, "atExplorerFoundation.lib")
#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "dslFoundation.lib")

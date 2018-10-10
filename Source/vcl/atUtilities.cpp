#include <vcl.h>
#pragma hdrstop
#include "atUtilities.h"
#include "dslStringUtils.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;

TTabSheet* getTabWithCaption(const string& c, TPageControl* pc)
{
    if(!pc)
    {
        return NULL;
    }

    for(int i = 0; i < pc->PageCount; i++)
    {
        if(compareStrings(stdstr(pc->Pages[i]->Caption), c, csCaseSensitive))
        {
            return pc->Pages[i];
        }
    }

    return NULL;
}

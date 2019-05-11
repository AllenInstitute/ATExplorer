#ifndef atTiffStackCreatorH
#define atTiffStackCreatorH
#include "atExplorerObject.h"
#include "atTiffStack.h"
#include "dslProcess.h"
//---------------------------------------------------------------------------
namespace at
{

using dsl::Process;
using dsl::StringList;

class ATE_CORE TiffStackCreator : public ExplorerObject
{
    public:
                                        TiffStackCreator(const string& imPath, const string&  wf);
                                        ~TiffStackCreator();
        void                            assignCallbacks(dsl::Callback enter, dsl::Callback progress, dsl::Callback onExit);
        void                            create(const StringList& fileNames);

    protected:
        string                          mImageMagickPath;
        string                          mWorkingFolder;
        string                          mConvertExe;
        TiffStack*                      mTheStack;

	    Process 						mAProcess;
        void                            onIMProcessFinished(void*, void*);
};

}

#endif

#ifndef atCreateATIFDataStateTablesThreadH
#define atCreateATIFDataStateTablesThreadH
#include "dslThread.h"
#include "dslStringList.h"
#include "atATIFDataProcessThread.h"
//---------------------------------------------------------------------------

namespace at
{
class ATE_DATA CreateATIFDataStateTablesThread : public ATIFDataProcessThread
{
	public:
							                CreateATIFDataStateTablesThread(ATIFData& d);
		virtual void                        run();

	private:
        void                                onDockerProgress(void* arg1, void* arg2);
		string 								createDockerCommand(const string& outFile, const string& projDir, int ribbon, int session, int section);
};

}
#endif

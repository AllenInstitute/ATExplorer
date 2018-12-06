#ifndef atCreateRawDataRenderStacksThreadH
#define atCreateRawDataRenderStacksThreadH
#include "dslThread.h"
#include "dslStringList.h"
#include "atATIFData.h"
#include <boost/function.hpp>
#include "atExplorerObject.h"
#include "atATIFDataProcessThread.h"
//---------------------------------------------------------------------------


namespace at
{
using dsl::StringList;
using dsl::Thread;


class ATE_DATA CreateRawDataRenderStacksThread : public ATIFDataProcessThread
{
	public:
							                CreateRawDataRenderStacksThread(ATIFData& d, DockerContainer* dc, const string& renderHost);
 		virtual void                        run();

	private:
        void                                onDockerProgress(void* arg1, void* arg2);
		string 								createDockerCommand(const string& stateTablePathP, const string& projDir);
};

}
#endif

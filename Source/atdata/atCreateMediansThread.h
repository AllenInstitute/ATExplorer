#ifndef atCreateMediansThreadH
#define atCreateMediansThreadH
#include "atATIFDataProcessThread.h"
//---------------------------------------------------------------------------

namespace at
{

class ATE_DATA CreateMediansThread : public ATIFDataProcessThread
{
	public:
							                CreateMediansThread(ATIFData& d);
		virtual void                        run();


	private:
};

}
#endif

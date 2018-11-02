#ifndef atPopulateATDataThreadH
#define atPopulateATDataThreadH
#include "dslThread.h"
#include "atATIFDataProcessThread.h"
//---------------------------------------------------------------------------


namespace at
{


class ATE_DATA PopulateATDataThread : public ATIFDataProcessThread
{
	public:
							                PopulateATDataThread(ATIFData& d);
		virtual void                        run();

	private:
};

}
#endif

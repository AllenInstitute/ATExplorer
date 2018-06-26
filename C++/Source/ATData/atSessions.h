#ifndef atSessionsH
#define atSessionsH
#include <vector>
#include "atATObject.h"
#include "atATDataExporter.h"

namespace at
{

using std::vector;

class Session;

//!Sessions is a container for individual AT "Sessions".
//!A session
//---------------------------------------------------------------------------
class ATDATA Sessions : public vector<Session*>, public ATObject
{
        public:
                                                Sessions();
                                                ~Sessions();
            Session*                            getFirstSession();
            Session*                            getNextSession();
            int                                 count(){return size();}

        protected:
        	vector<Session*>::iterator  		mSessionIterator;

};

}
#endif

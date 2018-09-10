#ifndef atSessionsH
#define atSessionsH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"

namespace ate
{

using std::vector;

class Session;

//!Sessions is a container for individual AT "Sessions".
//!A session
//---------------------------------------------------------------------------
class ATE_DATA Sessions : public vector<Session*>, public ExplorerObject
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

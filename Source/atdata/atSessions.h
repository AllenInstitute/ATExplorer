#ifndef atSessionsH
#define atSessionsH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"

namespace at
{

using std::vector;

class Session;

//!Sessions is a container for individual AT "Sessions".
//!A session
//---------------------------------------------------------------------------
class ATE_DATA Sessions : public ExplorerObject
{
        public:
                                                Sessions();
                                                ~Sessions();
			void 								clear();
            Session*                            getFirstSession();
            Session*                            getNextSession();
            int                                 count(){return mSessions.size();}
            void                                append(Session* s){mSessions.push_back(s);}

        protected:
        	vector<Session*>::iterator  		mSessionIterator;
            vector<Session*>                    mSessions;
};

}
#endif

#ifndef atSessionsH
#define atSessionsH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"
#include "dslSharedPointer.h"

namespace at
{

using std::vector;

class Session;

//!Sessions is a container for individual AT "Sessions".
//!A session

typedef std::tr1::shared_ptr<Session> SessionSP;
//---------------------------------------------------------------------------
class ATE_DATA Sessions : public ExplorerObject
{
        public:
                                                Sessions();
                                                ~Sessions();
			void 								clear();
            SessionSP                           getFirstSession();
            SessionSP                           getNextSession();
            int                                 count(){return mSessions.size();}
            void                                append(SessionSP s){mSessions.push_back(s);}

        protected:
        	vector<SessionSP>::iterator  		mSessionIterator;
            vector<SessionSP>                   mSessions;
};

}
#endif

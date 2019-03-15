#ifndef atSessionsH
#define atSessionsH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------
namespace at
{

using std::vector;

class Session;

//!Sessions is a container for individual AT "Sessions".
//!A session label need to be unique..
typedef std::shared_ptr<Session> SessionSP;
//---------------------------------------------------------------------------
class ATE_DATA Sessions : public ExplorerObject
{
    public:
                                            Sessions();
                                            ~Sessions();
        void 								clear();
        SessionSP                           getSession(int indx);
        SessionSP                           getSession(const string& lbl);
        SessionSP                           getFirstSession();
        SessionSP                           getNextSession();
        int                                 count();
        bool                                append(SessionSP s);
        int                                 getNumberOfChannels();

    protected:
        vector<SessionSP>::iterator  		mSessionIterator;
        vector<SessionSP>                   mSessions;
};

}
#endif

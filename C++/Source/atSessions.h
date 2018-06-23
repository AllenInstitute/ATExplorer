#ifndef atSessionsH
#define atSessionsH
#include "atATObject.h"
#include <vector>

namespace at
{

using std::vector;

class Session;

//!Sessions is a container for individual AT "Sessions". A Ribbon is a set of consecutive Sessions
//---------------------------------------------------------------------------
class Sessions : public vector<Session*>, public ATObject
{
        public:
                                    Sessions();
                                    ~Sessions();
            int                     count(){return size();}

        protected:


};

}
#endif

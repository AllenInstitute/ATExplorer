#ifndef atSessionsH
#define atSessionsH
#include "atATObject.h"

//!Sessions is a container for individual AT "Sessions". A Ribbon is a set of consecutive Sessions
//---------------------------------------------------------------------------
class Sessions : public ATObject
{

        public:
                            Sessions();
                            ~Sessions();

        protected:

        private:

};

Sessions::Sessions()
{}

Sessions::~Sessions()
{}
#endif

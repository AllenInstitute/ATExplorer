#ifndef atChannelsH
#define atChannelsH
#include "atATObject.h"
#include <vector>
#include "atChannel.h"
//---------------------------------------------------------------------------

namespace at
{

using std::vector;

//!The Channels class is a container for AT Channels
class Channels : public std::vector<Channel>, public ATObject
{

        public:
                            	Channels();
                            	~Channels();
            bool                append(const Channel& ch);
            bool                append(const Channels& chns);

        private:
            
};

}
#endif

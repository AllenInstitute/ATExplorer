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
class ATDATA Channels : public vector<Channel*>, public ATObject
{

        public:
                            	        Channels();
                            	        ~Channels();
            bool                        append(Channel* ch);
            bool                        append(const Channels& chns);
            Channel*                    getFirstChannel();
            Channel*                    getNextChannel();

        protected:
	        vector<Channel*>::iterator  mChannelIterator;
            
};

}
#endif

#ifndef atChannelsH
#define atChannelsH
#include "atExplorerObject.h"
#include <vector>
#include "atChannel.h"
//---------------------------------------------------------------------------

namespace ate
{

using std::vector;

//!The Channels class is a container for AT Channels
class ATE_DATA Channels : public vector<Channel*>, public ExplorerObject
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

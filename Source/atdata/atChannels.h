#ifndef atChannelsH
#define atChannelsH
#include "atExplorerObject.h"
#include <vector>
#include "atChannel.h"
#include "dslSharedPointer.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace at
{

using std::vector;
using dsl::shared_ptr;
using dsl::StringList;

typedef shared_ptr<Channel> ChannelSP;

//!The Channels class is a container for AT Channels
class ATE_DATA Channels : public ExplorerObject
{
    public:
                                    Channels();
                                    ~Channels();
        bool                        append(ChannelSP ch);
        bool                        append(const Channels& chns);
        ChannelSP                   getFirstChannel();
        ChannelSP                   getNextChannel();
        StringList                  asStringList();

    protected:
        vector<ChannelSP>::iterator mChannelIterator;
        vector<ChannelSP>           mChannels;
};

}
#endif

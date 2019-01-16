#ifndef atSessionH
#define atSessionH
#include "atExplorerObject.h"
#include "atChannel.h"
#include "atChannels.h"
//---------------------------------------------------------------------------

namespace at
{

class ATE_DATA Session : public ExplorerObject
{
    public:
                                    Session(const string& lbl);
                                    ~Session();
        virtual string        	    getTypeName() const;
        string                      getLabel() const {return mLabel;}
        int                         getID() const;
        bool        	            appendChannel(ChannelSP channel);
        ChannelSP                   getChannel(const string& channelLbl);
        ChannelSP                   getChannel(ChannelSP channel);

        ChannelSP                   getFirstChannel();
        ChannelSP                   getNextChannel();
        StringList                  getChannelLabels();
        bool                        operator==(const Session& s) const;
        int                         getNumberOfChannels();

    protected:
        string                      mLabel;
        Channels                    mChannels;
};

}

#endif

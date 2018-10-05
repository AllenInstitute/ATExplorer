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
            string          getLabel(){return mLabel;}
            bool        	appendChannel(ChannelSP channel);

            ChannelSP       getFirstChannel();
            ChannelSP       getNextChannel();
            StringList      getChannelLabels();

	protected:
            string          mLabel;
            Channels        mChannels;
};

}

#endif

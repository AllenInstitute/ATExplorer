#ifndef atChannelH
#define atChannelH
#include "atExplorerObject.h"
#include "atATDataExporter.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace at
{

using dsl::shared_ptr;
class Session;

class Channel;
typedef shared_ptr<Channel> ChannelSP;

//!A channel belong to a specific Session
class ATE_DATA Channel : public ExplorerObject
{
    public:
                                    Channel(const string& lbl, Session& s);
                                    ~Channel();
    	string                      getLabel() const {return mLabel;}
        bool                        operator==(const Channel& c) const;

    protected:
        string                      mLabel;
        Session&                    mSession;
};

}


#endif

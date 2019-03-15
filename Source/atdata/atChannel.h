#ifndef atChannelH
#define atChannelH
#include "atExplorerObject.h"
#include "atATDataExporter.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace at
{

class Session;
class Channel;
typedef std::shared_ptr<Channel> ChannelSP;

//!A channel belong to a specific Session
class ATE_DATA Channel : public ExplorerObject
{
    public:
                                    Channel(const string& lbl, Session& s);
                                    ~Channel();
        virtual string         		getTypeName() const;
    	string                      getLabel() const {return mLabel;}
        bool                        operator==(const Channel& c) const;

    protected:
        string                      mLabel;
        Session&                    mSession;
};

}


#endif

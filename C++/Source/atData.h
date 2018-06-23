#ifndef atDataH
#define atDataH
#include "atATObject.h"
#include "Poco/Path.h"
#include "atFileFolder.h"
#include "atRibbons.h"
#include "atSessions.h"
#include "atChannels.h"
#include "atSection.h"
//---------------------------------------------------------------------------
using Poco::Path;

namespace at
{

//!The ATData class abstracts ArrayTomography data
class ATData : public ATObject
{
    public:
                        	        ATData();

                                    //!populating a ATData object typically include
                                    //!parsing through a folder structure in descendant data
                                    //!type objects
        virtual bool                populate() = 0;
        virtual bool                validate() = 0;


        Ribbons*                    getRibbons();
        Ribbon*     	            getRibbon(int count);

                                    //!A session is the same as a "group of stains" => one or more channel data
        Sessions*                   getSessions();
        Channels                    getChannels();

                                    //!Utilities
        int                         getNumberOfRibbons();
        int                         getNumberOfSections();
		int                         getNumberOfTiles();

    protected:

                                    //A Ribbon contain consecutive sections,
                                    //Ribbons capture the "physical" properties of a ribbon, i.e. sections
        Ribbons                     mRibbons;

                                    //!A session denote a data acqusition 'session' using one or more
                                    //immuno fluorescent 'stains', channels.
                                    //Microscopy data is acquired during a session, and typically
                                    //ordered (in some format) on disk, representing tissue sections and ribbons
        Sessions                    mSessions;
};

}

#endif

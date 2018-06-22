#ifndef atDataH
#define atDataH
#include "atATObject.h"
#include "Poco/Path.h"
#include "atFileFolder.h"
#include "atRibbons.h"
#include "atSessions.h"
#include "atChannels.h"
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

        Sessions*                   getSessions();
        Channels*                   getChannels();

                                    //!Utilities
        int                         getNumberOfRibbons();
        int                         getNumberOfSections();
		int                         getNumberOfTiles();

    protected:

                                    //A Ribbon contain consecutive sections
        Ribbons                     mRibbons;

                                    //!A session denote a data acqusition 'session' using one or more
                                    //immuno fluorescent 'stains'
                                    //Microscopy data is acquired during a session, and typically
                                    //ordered (in some format) on disk, representing tissue sections and ribbons
        Sessions                    mSessions;

                                    //!A IF stain fluoresces at a particular wavelength, i.e. a "channel". E.g. DAPI, GFP etc.
                                    //During a session, several channels can be imaged 'in series'.
        Channels                    mChannels;
};

}

#endif

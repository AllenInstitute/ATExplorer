#ifndef atATDataH
#define atATDataH
#include "atExplorerObject.h"
#include "Poco/Path.h"
#include "atFileFolder.h"
#include "atRibbons.h"
#include "atSessions.h"
#include "atChannels.h"
#include "atSection.h"
#include "atATDataUtils.h"
//---------------------------------------------------------------------------

namespace ate
{

//!The ATData class abstracts ArrayTomography data
class ATE_DATA ATData : public ExplorerObject
{
    public:
                        	        ATData(const Path& basePath);
		virtual ATDataFileFormat    getFileFormat() = 0;
        Path                        getBasePath();

                                    //!populating a ATData object typically include
                                    //!parsing through a folder structure in descendant data
                                    //!type objects
        virtual bool                populate() = 0;
        virtual bool                validate() = 0;


        Ribbons*                    getRibbons();
        Ribbon*     	            getRibbon(int count);
        Ribbon*     	            getFirstRibbon();
        Ribbon*     	            getNextRibbon();

                                    //!A session is the same as a "group of stains" => one or more channel data
        Sessions*                   getSessions();
        Session*                    getFirstSession();
        Session*                    getNextSession();

        Channels*                   getChannels(Session* session);
        Channel*                    getFirstChannel(Session* session);
        Channel*                    getNextChannel(Session* session);

                                    //!Utilities
        int                         getNumberOfRibbons();
        int                         getNumberOfSections();
		int                         getNumberOfTiles();

    protected:
                                    //A Ribbon contain consecutive sections,
                                    //Ribbons capture the "physical" properties of a ribbon and sections
        Ribbons                     mRibbons;

                                    //!A session denote a data acqusition 'session' using one or more
                                    //immuno fluorescent 'stains', channels.
                                    //Microscopy data is acquired during a session, and typically
                                    //ordered (in some format) on disk, representing tissue sections and ribbons
        Sessions                    mSessions;

                                    //!The data need to have a format on disk..
        ATDataFileFormat            mFileFormat;

                                	//!Basepath of raw data. All IF data need to be accesible
                            	    //below this folder
        Path	     			    mBasePath;
};

}

#endif

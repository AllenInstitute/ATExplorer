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
#include <boost/function.hpp>
//---------------------------------------------------------------------------

namespace at
{

typedef boost::function<void(void*, void*, void*)> ATDataPopulateCallback;

//!The ATData class abstracts ArrayTomography data in terms of Ribbons, Sections, Sessions etc.

class ATE_DATA ATData : virtual public ExplorerObject
{
    public:
                        	                    ATData(const Path& basePath = Path("<not set>"));
		virtual            	                    ~ATData();
        virtual string                    		getTypeName() const;
        void                                    assignOnPopulateCallbacks(ATDataPopulateCallback onenter, ATDataPopulateCallback onprogress, ATDataPopulateCallback onexit);
		virtual ATDataFileFormat                getFileFormat() = 0;
        Path                                    getBasePath() const;
        virtual bool                            setBasePath(const string& p);

                                        		//!Return some information about the current data
        string                                  getInfo();
        virtual string                          getInfoJSON();

                                                //!Resets the data object, excepts the basepath
        virtual void                            reset();

                                                //!populating a ATData object typically include
                                                //!parsing through a folder structure in descendant data
                                                //!type objects
                                                //-- suspicious boolean??
        virtual bool                            populate(const bool& exitPopulation) = 0;
        virtual bool                            validate() = 0;
        int                                     getNumberOfRibbons();
        Ribbons*                                getRibbons();

                                                //!Start at 1(!)
        RibbonSP     	                        getRibbon(int count);
        RibbonSP     	                        getFirstRibbon();
        RibbonSP     	                        getNextRibbon();

                                                //!A session is the same as a "group of stains" => one or more channel data
		int                                     getNumberOfSessions();
        Sessions*                               getSessions();
        SessionSP                               getFirstSession();
        SessionSP                               getNextSession();

        StringList                              getChannelLabelsForSession(SessionSP session);

                                                //!Utilities
        int                                     getNumberOfSections();
		int                                     getNumberOfTiles();
		int                                     getNumberOfChannels();

//        Sections                                getSections(const ChannelSP channel);

    protected:
                                	            //!Basepath of raw data. All raw AT data need to be accesible
                            	                //below this folder
        Path	     			                mBasePath;

                                                //!The data need to have a format on disk..
        ATDataFileFormat                        mFileFormat;

                                                //A Ribbon contain consecutive sections,
                                                //Ribbons capture the "physical" properties of a ribbon and sections
        Ribbons                                 mRibbons;

                                                //!A session denote a data acqusition 'session' using one or more
                                                //immuno fluorescent 'stains', channels.
                                                //Microscopy data is acquired during a session, and typically
                                                //ordered (in some format) on disk, representing tissue sections and ribbons
        Sessions                                mSessions;

                                                //!These callbacks can be used by clients to get feedback on progress when
                                                //!populating the data object
		ATDataPopulateCallback                  onStartingPopulating;
		ATDataPopulateCallback                  onProgressPopulating;
		ATDataPopulateCallback                  onFinishedPopulating;

                                                //!If we need to stop the population of data
        const bool*                             mStopPopulation;
};

}

#endif

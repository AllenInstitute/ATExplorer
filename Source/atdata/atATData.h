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

typedef boost::function<void(void*, void*)> ATDataPopulateCallback;

//!The ATData class abstracts ArrayTomography data
class ATE_DATA ATData : public ExplorerObject
{
    public:
                        	                    ATData(const Path& basePath);
		virtual            	                    ~ATData();
        void                                    assignOnPoplateCallbacks(ATDataPopulateCallback onenter, ATDataPopulateCallback onprogress, ATDataPopulateCallback onexit);
		virtual ATDataFileFormat                getFileFormat() = 0;
        Path                                    getBasePath();

                                        		//!Return some information about the current data
        string                                  getInfo();

                                                //!Resets the data object, excepts the basepath
        virtual void                            reset();

                                                //!populating a ATData object typically include
                                                //!parsing through a folder structure in descendant data
                                                //!type objects
        virtual bool                            populate() = 0;
        virtual bool                            validate() = 0;
        Ribbons*                                getRibbons();
        RibbonSP     	                        getRibbon(int count);
        RibbonSP     	                        getFirstRibbon();
        RibbonSP     	                        getNextRibbon();

                                                //!A session is the same as a "group of stains" => one or more channel data
        Sessions*                               getSessions();
        SessionSP                               getFirstSession();
        SessionSP                               getNextSession();
        StringList                              getChannelLabelsForSession(SessionSP session);

                                                //!Utilities
        int                                     getNumberOfRibbons();
        int                                     getNumberOfSections();
		int                                     getNumberOfTiles();

    protected:
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

                                	            //!Basepath of raw data. All IF data need to be accesible
                            	                //below this folder
        Path	     			                mBasePath;

                                                //!These callbacks can be used by clients to get feedback on progress when
                                                //!populating the data
		ATDataPopulateCallback                  onStartingPopulating;
		ATDataPopulateCallback                  onProgressPopulating;
		ATDataPopulateCallback                  onFinishedPopulating;


};

}

#endif

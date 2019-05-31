#ifndef atATIFDataH
#define atATIFDataH
#include "atATData.h"
//---------------------------------------------------------------------------

namespace at
{

//!The ATIFData class maps the dataformats used in Smith Lab..
//!Some assumptions:
//!Number of tiles for a particular section, for a particular ribbon, are equal across channels(sessions)
//!A section do always belong to a ribbon

class ATIFData;
typedef shared_ptr<ATIFData> ATIFDataSP;

class ATE_DATA ATIFData : public ATData
{
    public:
                    					            ATIFData(const string& basePath);
                    					            ATIFData(const Path&   basePath);
        virtual bool                                setBasePath(const string& bp);
		ATDataFileFormat            	            getFileFormat();
        virtual void                                reset();
        virtual bool        			            validate();
        virtual bool                                populate(const bool& exitPopulation);
		virtual string 								getNumberOfSectionsInRibbonsJSON();
        virtual string                              getInfoJSON();
        virtual string                              getSummaryJSON();

                                                    //!Ribbonfolder functions..
		FileFolders                                 getRibbonFolders();
		StringList                                  getRibbonBaseFolders();

        FileFolderSP					            getRibbonFolder(int fldr);

                                                    //!Get root folder for Ribbon Folders
        FileFolderSP 	       			            getRibbonsDataFolder();

        int                 			            getNumberOfRibbonFolders();

		FileFolders						            getSessionFolders(FileFolderSP ribbonFolder);
		StringList						            getSessionBaseFolders();

   		FileFolders                                 getChannelFolders(FileFolderSP sessionFolder);

        int	                                        getNumberOfStateTables(bool refresh = false);

        StringList                                  getStateTables();

    protected:
        Path 							            mRibbonsFolderPath;
        FileFolderSP			                    mRibbonsDataFolder;
        FileFolderSP   	    			            mProcessedDataFolder;
        FileFolderSP        			            mScriptsDataFolder;
        StringList                                  mStateTables;

        bool                                        populateRibbons();
        bool                                        populateSessions();
        bool                                        populateStateTables();
};
}
#endif

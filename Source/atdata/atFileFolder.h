#ifndef atFileFolderH
#define atFileFolderH
#include <set>
#include <string>
#include <utility>
//#include <boost/enable_shared_from_this.hpp>
#include <memory>
#include "Poco/Path.h"
#include "atFileSystemObject.h"
#include "dslStringList.h"
#include "atFileFolders.h"
//---------------------------------------------------------------------------

namespace at
{

using std::pair;
using std::vector;
using std::set;
using std::string;
using Poco::Path;
using dsl::StringList;

struct FolderInfo
{
				    FolderInfo(int folders = 0, int files = 0)
                    : NrOfFolders(0), NrOfFiles(0){}
    int NrOfFolders;
    int NrOfFiles;
};


//!A File folder is FileSystem object.
class ATE_DATA FileFolder : public FileSystemObject, public std::enable_shared_from_this<FileFolder>
{
    public:
                            		FileFolder(const Path& name, FileFolderSP parent = FileFolderSP());
                            		~FileFolder();
        void                        reset();
        FileFolderSP                getFirstSubFolder();
        FileFolderSP                getNextSubFolder();

        FileFolderSP  				getSubFolder(const Path& p);
        FileFolders         		getSubFolders(const Path& subPath = Path("."));
        const set<string>&          getFiles(const string& globPattern = "*.*");
        StringList          		getSubFoldersAsList();
        bool                        isPresent(FileSystemObject* child);
        void 				        addSubFolder(FileFolderSP child);
        bool 				        removeChild(FileSystemObject* child);
        string						getLastPartOfPath();
        string                      directoryName(int n);
        FolderInfo                	scan();
        FolderInfo                  getFolderInfo();

    private:
	    FileFolders					mSubFolders;
        set<string>                 mFiles;
        FolderInfo                  mFolderInfo;
};

}
#endif

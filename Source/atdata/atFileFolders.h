#ifndef atFileFoldersH
#define atFileFoldersH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace at
{
class FileFolder;
using std::vector;

typedef std::shared_ptr<FileFolder>  FileFolderSP;

class ATE_DATA FileFolders : public ExplorerObject
{
    public:
                                        FileFolders();
                                        ~FileFolders();
                                        FileFolders(const FileFolders& f);
        FileFolders&                    operator=(const FileFolders& rhs);
        FileFolderSP                    operator[](int i);
        FileFolderSP                    operator[](int i) const;

        void                            reset();
        FileFolderSP    				getFirst();
        FileFolderSP    				getNext();

        void                            append(FileFolderSP ff);
        int             				count() const {return mFolders.size();}

    protected:
       vector<FileFolderSP>::iterator   mFolderIterator;
       vector<FileFolderSP>             mFolders;
};

}

#endif

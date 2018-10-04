#ifndef atFileFoldersH
#define atFileFoldersH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"
//---------------------------------------------------------------------------

namespace at
{
class FileFolder;
using std::vector;

class ATE_DATA FileFolders : public ExplorerObject
{
    public:
                                        FileFolders();
                                        ~FileFolders();
                                        FileFolders(const FileFolders& f);
        FileFolders&                    operator=(const FileFolders& rhs);
        FileFolder*                     operator[](int i);
        FileFolder*                     operator[](int i) const;

        void                            reset();
        FileFolder*     				getFirst();
        FileFolder*     				getNext();

        void                            append(FileFolder*);
        int             				count() const {return mFolders.size();}

    protected:
       vector<FileFolder*>::iterator    mFolderIterator;
       vector<FileFolder*>              mFolders;
};

}

#endif

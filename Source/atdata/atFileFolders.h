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
            FileFolder*     				getFirst();
            FileFolder*     				getNext();
            FileFolder*                     operator[](int i);
            void                            append(FileFolder*);


            int             				count(){return mFolders.size();}

        protected:
           vector<FileFolder*>::iterator    mFolderIterator;
           vector<FileFolder*>              mFolders;
};

}

#endif

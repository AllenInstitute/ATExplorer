#ifndef atFileFoldersH
#define atFileFoldersH
#include <vector>
#include "atExplorerObject.h"
#include "atATDataExporter.h"
//---------------------------------------------------------------------------

namespace ate
{
class FileFolder;
using std::vector;

class ATE_DATA FileFolders : public vector<FileFolder*>, public ExplorerObject
{

        public:
                            				FileFolders();
                            				~FileFolders();
            FileFolder*     				getFirst();
            FileFolder*     				getNext();


            int             				count(){return size();}

        protected:
           vector<FileFolder*>::iterator    mFolderIterator;

        private:

};

}

#endif

#ifndef atFileFoldersH
#define atFileFoldersH
#include <vector>
#include "atATObject.h"
#include "atATDataExporter.h"
//---------------------------------------------------------------------------

namespace at
{
class FileFolder;
using std::vector;

class ATDATA FileFolders : public vector<FileFolder*>, public ATObject
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

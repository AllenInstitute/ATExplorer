#ifndef atFileFoldersH
#define atFileFoldersH
#include "atATObject.h"
#include <vector>
//---------------------------------------------------------------------------

namespace at
{
class FileFolder;
using std::vector;

class FileFolders : public vector<FileFolder*>, public ATObject
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

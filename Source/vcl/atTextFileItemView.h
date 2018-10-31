#ifndef atTextFileItemViewH
#define atTextFileItemViewH
#include "dslObserver.h"
#include "atProjectItemTabbedView.h"
#include "TTextFileFrame.h"
#include <memory>
//---------------------------------------------------------------------------

namespace at
{

using std::unique_ptr;
using dsl::Subject;
using dsl::SubjectEvent;

class TextFile;

//VCL frames can't do multiple inheritance. This class is therefore necessary, for "observing" reasons..
//The view manages the VCL frame..
class PACKAGE TextFileItemView : public ProjectItemTabbedView
{
    public:
                                            TextFileItemView(TPageControl& pc, TextFile& rp);
        virtual            		            ~TextFileItemView();
        virtual void                        update(Subject* theChangedSubject, SubjectEvent se = dsl::Ping);


    protected:
        unique_ptr<TTextFileFrame>  		mTextFileFrame;
};

}

#endif

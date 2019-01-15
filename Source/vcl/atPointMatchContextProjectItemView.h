#ifndef atPointMatchCollectionProjectItemViewH
#define atPointMatchCollectionProjectItemViewH
#include "atProjectItemTabbedView.h"
#include "TPointMatchCollectionFrame.h"
#include <memory>
#include "atATExplorer.h"
//---------------------------------------------------------------------------

namespace at
{

using std::unique_ptr;
using dsl::Subject;
using dsl::SubjectEvent;
using at::ATExplorer;
class PointMatchCollectionProject;

//VCL frames can't do multiple inheritance. This class is therefore necessary, for "observing" reasons..
//The view manages the VCL frame..
class PACKAGE PointMatchCollectionProjectItemView : public ProjectItemTabbedView
{
    public:
                                            PointMatchCollectionProjectItemView(TPageControl& pc, ATExplorer& e, PointMatchCollectionProject& rp);
        virtual                             ~PointMatchCollectionProjectItemView();

    protected:
        unique_ptr<TPointMatchCollectionFrame>    	mPointMatchCollectionFrame;
};

}

#endif

#ifndef atProjectsH
#define atProjectsH
#include "atATObject.h"
#include "dslProject.h"
#include "dslSharedPointer.h"
#include <list>
//---------------------------------------------------------------------------

//Container for ATProjects
namespace at
{

using std::list;
using dsl::Project;
class Project;

//Simple container holding projects

class Projects : public ATObject
{

    public:
                                			    Projects();
                                			    ~Projects();
        void                    			    append(Project* p);
        void                    			    remove(Project* p);
        Project*                                selectFirst();
        Project*                                selectLast();

        bool                                    selectProject(Project* p);
        Project*					          	getRootProject(Project* p);

        Project*                                getCurrent();
        Project*                                getFirst();
        Project*                                getNext();
        Project*                                getPrevious();
        Project*                                getLast();
        int                                     count();

    protected:
        list<Project* >         	            mProjects;
        list<Project* >::iterator               mCurrentProjectIter;
};

}


#endif

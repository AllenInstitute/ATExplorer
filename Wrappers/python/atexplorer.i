%module(docstring="Array Tomography Library for Python (atexplorer), (c) 2016-2018 Allen Institute for BrainScience",threads="1", directors="0" ) atexplorer

// ************************************************************
// Module Includes
// ************************************************************
%{
#include "dslObject.h"
#include "dslLogger.h"
#include "dslLogOutput.h"
#include "atExplorerObject.h"
#include "atExplorerCore.h"
#include "atATData.h"
#include "atATIFData.h"
#include "atRibbon.h"
#include "atRibbons.h"
#include "atSection.h"
#include "atSections.h"
#include  <string>

using namespace dsl;
using namespace std;
using namespace at;
%}
 
//The atexplorer module is using many features from dsl
%include "dsl.i"
%include "std_sstream.i"
%include "std_vector.i"
%include <boost_shared_ptr.i>
%shared_ptr(at::Ribbon)

#define ATE_CORE
#define ATE_DATA
//ATCore header only contains a few utlity functions, e.g. getVersion

%include "Poco/Path.h"
%include "dslLogger.h"
%include "dslLogging.h"
%include "dslLogOutput.h"
%include "dslSharedPointer.h"

%include "atExplorerCore.h"
%include "atRibbon.h"
%include "atRibbons.h"
%include "atSection.h"
%include "atSections.h"
%include "atExplorerObject.h"
%include "atATData.h"
%include "atATIFData.h"


//Add alias function to class Ribbon
%extend at::Ribbon {
    int getSectionCount() {
    return $self->sectionCount();
  }

}

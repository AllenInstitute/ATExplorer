#ifndef atATEObjectH
#define atATEObjectH
#include "atExplorerCoreExporter.h"
#include <string>
//---------------------------------------------------------------------------

namespace at
{

using std::string;
class ATE_CORE ATEObject
{
	public:
    							        ATEObject(){}
		virtual					        ~ATEObject() = 0;
        virtual const string 	        getTypeName() const;
};
}
#endif

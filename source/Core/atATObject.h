#ifndef atATObjectH
#define atATObjectH
#include "atCoreExporter.h"
#include <string>
//---------------------------------------------------------------------------

namespace at
{

using std::string;
class AT_CORE ATObject
{
	public:
    							 ATObject(){}
		virtual					~ATObject() = 0;
        virtual const string 	getTypeName() const;
};
}
#endif

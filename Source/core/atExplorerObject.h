#ifndef atExplorerObjectH
#define atExplorerObjectH
#include "atExplorerCoreExporter.h"
#include <string>
//---------------------------------------------------------------------------

namespace ate
{

using std::string;
class ATE_CORE ExplorerObject
{
	public:
    							        ExplorerObject();
		virtual					        ~ExplorerObject() = 0;
        virtual const string 	        getTypeName() const;
};
}
#endif
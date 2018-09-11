#ifndef atExceptionsH
#define atExceptionsH
#include "atExplorerCoreExporter.h"
#include "atExplorerObject.h"
#include <exception>
#include <string>
#include <sstream>
//---------------------------------------------------------------------------
using std::string;
using std::stringstream;

namespace at
{
    class ATE_CORE Exception : public std::exception, public ExplorerObject
    {
        public:
                                                Exception(const string& desc);
                                                Exception(const stringstream& msg);
            virtual                             ~Exception() throw();
            virtual const char*                 what() const throw();
            string                              Message() const;

        protected:
                                                //ATException message
            string                              mMessage;
    };

    class ATE_CORE FileSystemException : public Exception
    {
        public:
                                                FileSystemException(const string& desc) : Exception(desc){}
                                                FileSystemException(const stringstream& msg) : Exception(msg){}
    };

    class ATE_CORE DataException : public Exception
    {
        public:
                                                DataException(const string& desc) : Exception(desc){}
                                                DataException(const stringstream& msg) : Exception(msg){}
    };


}
#endif

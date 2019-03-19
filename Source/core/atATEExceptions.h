#ifndef atATEExceptionsH
#define atATEExceptionsH
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

class ATE_CORE FileSystemException : public at::Exception
{
    public:
                                            FileSystemException(const string& desc) : at::Exception(desc){}
                                            FileSystemException(const stringstream& msg) : at::Exception(msg){}
};

class ATE_CORE DataException : public Exception
{
    public:
                                            DataException(const string& desc) : at::Exception(desc){}
                                            DataException(const stringstream& msg) : at::Exception(msg){}
};

class ATE_CORE PointMatchCollectionCTORException : public Exception
{
    public:
                                            PointMatchCollectionCTORException(const string& desc) : at::Exception(desc){}
                                            PointMatchCollectionCTORException(const stringstream& msg) : at::Exception(msg){}
};

}
#endif

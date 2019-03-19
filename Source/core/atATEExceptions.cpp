#pragma hdrstop
#include "atATEExceptions.h"
//---------------------------------------------------------------------------

namespace at
{
    Exception::Exception(const string& desc)
    :
    mMessage(desc)
    {}

    Exception::Exception(const stringstream& msg)
    :
    mMessage(msg.str())
    {}

    Exception::~Exception() throw()
    {}


    const char* Exception::what() const throw()
    {
        return mMessage.c_str();
    }

    string Exception::Message() const
    {
        return mMessage;
    }

}

#ifndef CommandLineParametersH
#define CommandLineParametersH
#include <string>
//#include "dslLogger.h"
//---------------------------------------------------------------------------
using std::string;
using dsl::Logger;

string Usage(const string& prg);
class Args
{
    public:
                                        Args();
        virtual                        ~Args(){}
        dsl::LogLevel                   CurrentLogLevel;    //option d:
        string                          DataInputFolder;    //option m:

        string                          version;
};

#endif

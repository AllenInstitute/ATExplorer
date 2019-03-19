#pragma hdrstop
#include <iomanip>
#include <sstream>
#include "Args.h"
//---------------------------------------------------------------------------

using namespace std;
using namespace dsl;
Args::Args()
:
CurrentLogLevel(LogLevel::lWarning),
DataInputFolder(""),
version("0.5.0")
{}

string Usage(const string& prg)
{
    Args args;
    stringstream usage;
    usage<< "app.exe is a command line driven app\n\n";
    usage << "\nUSAGE for \'"<< getFileNameNoPath(prg) <<"\'\n\n";
    usage<<left;
    usage<<setfill('.');
    usage<<setw(25)<<"-d<debug level>"              <<" Debug levels: Error, Warning, Info, Debug. Default: Info\n";
    usage<<setw(25)<<"--version"                    <<" Prints the current version.\n";
    usage<<setw(25)<<"--inputdatafolder"            <<" Input data folder.\n";
    usage<<setw(25)<<"-? "                          <<" Shows the help screen.\n";

    usage<<"Version: "<<args.version<<"\n\n";
    usage<<"\nDune Scientific Library, 2001-2019\n";
    return usage.str();
}


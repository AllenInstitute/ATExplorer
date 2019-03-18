#pragma hdrstop
#include "dslStringList.h"
#include "dslUtils.h"
#include "dslException.h"
#include "optionparser/ezOptionParser.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace std;
using namespace ez;
using namespace dsl;

void Usage(ezOptionParser& opt)
{
	std::string usage;
	opt.getUsage(usage);
	std::cout << usage;
};

int main(int argc, const char * argv[])
{

	ezOptionParser opt;
    setupOptions(&opt);

	opt.parse(argc, argv);

	if (opt.isSet("-h"))
    {
		Usage(opt);
		return 1;
	}

	if (opt.lastArgs.size() < 2)
    {
		Usage(opt);
		return 1;
	}

//	std::vector<std::string> badOptions;
//	int i;
//	if(!opt.gotRequired(badOptions)) {
//		for(i=0; i < badOptions.size(); ++i)
//			std::cerr << "ERROR: Missing required option " << badOptions[i] << ".\n\n";
//		Usage(opt);
//		return 1;
//	}
//
//	if(!opt.gotExpected(badOptions)) {
//		for(i=0; i < badOptions.size(); ++i)
//			std::cerr << "ERROR: Got unexpected number of arguments for option " << badOptions[i] << ".\n\n";
//
//		Usage(opt);
//		return 1;
//	}
//
//	std::string firstArg;
//	if (opt.firstArgs.size() > 0)
//		firstArg = *opt.firstArgs[0];
//
//	bool flag = false;
//	if (opt.isSet("-f")) {
//		flag = true;
//	}
//
//	std::vector<int> list;
//	opt.get("-lst")->getInts(list);
//	std::cout << "\nList:";
//	for(int j=0; j < list.size(); ++j)
//		std::cout << " " << list[j];
//
//	std::cout << std::endl;

	return 0;
}

////using namespace dsl;
////void ProcessCommandLineArguments(int argc, char* argv[], Args& args);
//int main(int argc, char * argv[])
//{
////    bool doContinue = true;
//////    Args args;
////    try
////    {
////        gLogger.logToConsole(true);
////
////        if(argc < 2)
////        {
////            cout << Usage(argv[0]) << endl;
////            exit(0);
////        }
////
////        ProcessCommandLineArguments(argc, argv, args);
////        gLogger.setLogLevel(args.CurrentLogLevel);
////
////        Log(lDebug) << "Working Directory: " << getCWD() << endl;
////
////    }
////    catch(dsl::DSLException& ex)
////    {
////        Log(lError)<<"Application exception occurred: "<<ex.what()<<endl;
////    }
////    catch(...)
////    {
////        Log(lError)<<"There was an unknown problem.."<<endl;
////    }
////
////    Log(lInfo)<<"Application is exiting...";
//    return 0;
//}
//
//
void setupOptions(ezOptionParser& opt)
{
	opt.overview 	= "atcli: command line interface to the ATExplorer backend.";
	opt.syntax 		= "atcli --dataroot /nas1/data/M33 [OPTIONS]";
	opt.example 	= "atcli --dataroot /nas1/data/M33 --pipeline stitch --sections 1-3,5\n\n";
	opt.footer 		= "ATExplorer CLI 0.1  Copyright (C) 2019 Allen Institute for Brain Science\nThis program is free and without warranty.\n";

	opt.add(
		"", // Default.
		0, // Required?
		0, // Number of args expected.
		0, // Delimiter if expecting multiple args.
		"Display usage instructions.", // Help description.
		"-h",     // Flag token.
		"-help",  // Flag token.
		"--help", // Flag token.
		"--usage" // Flag token.
	);

	opt.add(
		"", // Default.
		0, // Required?
		0, // Number of args expected.
		0, // Delimiter if expecting multiple args.
		"Absolute path to root folder of input data (project) to process", // Help description.
		"-d",     // Flag token.
		"-dr",   // Flag token.
		"--dataroot" // Flag token.
	);

//	opt.add(
//		"", // Default.
//		0, // Required?
//		-1, // Number of args expected.
//		',', // Delimiter if expecting multiple args.
//		"Lists of arbitrary lengths.", // Help description.
//		"-l",    // Flag token.
//		"-lst",  // Flag token.
//		"-list",  // Flag token.
//		"--list" // Flag token.
//	);
//
//	opt.add(
//		"hello", // Default.
//		1, // Required?
//		1, // Number of args expected.
//		0, // Delimiter if expecting multiple args.
//		"Single string.", // Help description.
//		"-s", // Flag token.
//		"-str", // Flag token.
//		"-string", // Flag token.
//		"--string" // Flag token.
//	);
//
//	opt.add(
//		"0,1", // Default.
//		0, // Required?
//		2, // Number of args expected.
//		',', // Delimiter if expecting multiple args.
//		"Integer placeholder.", // Help description.
//		"-i", // Flag token.
//		"-int", // Flag token.
//		"-integer", // Flag token.
//		"--integer" // Flag token.
//	);
//
//	opt.add(
//		"", // Default.
//		0, // Required?
//		1, // Number of args expected.
//		0, // Delimiter if expecting multiple args.
//		"Unsigned long placeholder.", // Help description.
//		"-ul", // Flag token.
//		"-ulong" // Flag token.
//	);
//
//	opt.add(
//		"", // Default.
//		0, // Required?
//		1, // Number of args expected.
//		0, // Delimiter if expecting multiple args.
//		"Float placeholder.", // Help description.
//		"-float" // Flag token.
//	);
//
//	opt.add(
//		"", // Default.
//		0, // Required?
//		1, // Number of args expected.
//		0, // Delimiter if expecting multiple args.
//		"Double placeholder.", // Help description.
//		"-double" // Flag token.
//	);

}

#ifndef atATDataExporterH
#define atATDataExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define ATDATA
    #else
        #if defined(EXPORT_ATDATA)
            #define ATDATA __declspec(dllexport)
        #else
            #define ATDATA __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_ATDATA
#endif

#endif

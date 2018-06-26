#ifndef atATDataExporterH
#define atATDataExporterH

#if defined (_WIN32)
    #if defined(AT_STATIC)
        #define AT_CORE
    #else
        #if defined(AT_EXPORT_ATDATA)
            #define AT_DATA __declspec(dllexport)
        #else
            #define AT_DATA __declspec(dllimport)
        #endif
    #endif
#else
    #define AT_ATDATA
#endif

#endif

#ifndef atATDataExporterH
#define atATDataExporterH

#if defined (_WIN32)
    #if defined(EXPORT_AT_DATA)
        #define AT_DATA __declspec(dllexport)
    #else
        #define AT_DATA __declspec(dllimport)
    #endif
#else
    #define AT_DATA
#endif

#endif

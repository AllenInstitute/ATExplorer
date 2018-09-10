#ifndef atATDataExporterH
#define atATDataExporterH

#if defined (_WIN32)
    #if defined(EXPORT_ATE_DATA)
        #define ATE_DATA __declspec(dllexport)
    #else
        #define ATE_DATA __declspec(dllimport)
    #endif
#else
    #define ATE_DATA
#endif

#endif

#ifndef atExplorerCoreExporterH
#define atExplorerCoreExporterH

#if defined (_WIN32)
    #if defined(EXPORT_AT_E_CORE)
        #define AT_E_CORE __declspec(dllexport)
    #else
        #define AT_E_CORE __declspec(dllimport)
    #endif
#else
    #define AT_E_CORE
#endif

#endif

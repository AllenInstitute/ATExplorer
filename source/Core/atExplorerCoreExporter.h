#ifndef atExplorerCoreExporterH
#define atExplorerCoreExporterH

#if defined (_WIN32)
    #if defined(EXPORT_ATE_CORE)
        #define ATE_CORE __declspec(dllexport)
    #else
        #define ATE_CORE __declspec(dllimport)
    #endif
#else
    #define ATE_CORE
#endif

#endif

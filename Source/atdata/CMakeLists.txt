SET(target atExplorerData)

INCLUDE_DIRECTORIES(
.
./../core
./../../ThirdParty
${ATEXPLORER_ROOT}
${ATEXPLORER_ROOT}/source/core
${CG_BOOST_ROOT}
${TR1_ROOT}
${TP_INCLUDES}
${TP_INCLUDES}/dsl
${TP_INCLUDES}/atexplorer
)

SET(src
atATData
atATDataUtils
atChannels
atFile
atFileFolders
atATIFData
atRibbons
atSections
atSessions
atTiles.cpp
atChannel
atFileFolder
atFileSystemObject
atRibbon
atSection
atSession
atTile
./../../ThirdParty/mkjson/mkjson.cpp
)

#===== Shared library
if(BUILD_SHARED_LIBS)
    message("Building shared ATData lib")
    ADD_LIBRARY(${target} SHARED
    ${src}
    )

    SET_PROPERTY(TARGET ${target}  PROPERTY COMPILE_DEFINITIONS 
    EXPORT_ATE_DATA
    )

    TARGET_LINK_LIBRARIES(${target} 
        atExplorerCore
        ${CMAKE_INSTALL_PREFIX}/lib/dslFoundation.lib
        ${CMAKE_INSTALL_PREFIX}/lib/poco_foundation.lib
    )

    INSTALL(    
    TARGETS ${target} 
    RUNTIME DESTINATION bin COMPONENT core
    LIBRARY DESTINATION lib COMPONENT core
    ARCHIVE DESTINATION lib COMPONENT core
    )            
endif()

#===== General Installs
if(INSTALL_CXX_LIBS)
FILE (GLOB headers *.h)
INSTALL (   FILES ${headers}			 	
            DESTINATION include/atexplorer 
            COMPONENT cxx_headers)

endif()


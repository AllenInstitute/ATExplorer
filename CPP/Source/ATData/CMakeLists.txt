SET(target atData)

INCLUDE_DIRECTORIES(
.
${ATEXPLORER_ROOT}
${ATEXPLORER_ROOT}/CPP/source
${CG_BOOST_ROOT}
${TR1_ROOT}
${THIRD_PARTY_INSTALL_PREFIX}/include
${THIRD_PARTY_INSTALL_PREFIX}/include/dsl
${THIRD_PARTY_INSTALL_PREFIX}/include/atexplorer
)

SET(src
atATData
atATIFDataUtils
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
)

link_directories(
${THIRD_PARTY_INSTALL_PREFIX}/lib
)


#===== Shared library
if(BUILD_SHARED_LIBS)
    message("Building shared ATData lib")
    ADD_LIBRARY(${target} SHARED
    ${src}
    )

    SET_PROPERTY(TARGET ${target}  PROPERTY COMPILE_DEFINITIONS 
    EXPORT_ATDATA
    )

    TARGET_LINK_LIBRARIES(${target} 
        ${CMAKE_INSTALL_PREFIX}/lib/atCore.lib
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


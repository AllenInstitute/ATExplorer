SET(target atExplorerCore)

INCLUDE_DIRECTORIES(
.
${ATEXPLORER_ROOT}
${ATEXPLORER_ROOT}/source/core
${CG_BOOST_ROOT}
${TR1_ROOT}
${TP_INCLUDES}
${TP_INCLUDES}/dsl
)

SET(src
atExplorerCore
atExplorerObject
atATEExceptions
#atATProjectItem
#atATProjectItems
#atATDataProjectItem
#atRenderProjectItem
)

#===== Shared library
if(BUILD_SHARED_LIBS)
    message("Building shared ATExplorerCore lib")
    ADD_LIBRARY(${target} SHARED
    ${src}
    )

    SET_PROPERTY(TARGET ${target}  PROPERTY COMPILE_DEFINITIONS 
    EXPORT_ATE_CORE
    )

    TARGET_LINK_LIBRARIES(${target} 
#        ${CMAKE_INSTALL_PREFIX}/lib/dslFoundation
#        ${CMAKE_INSTALL_PREFIX}/lib/poco_foundation.lib
#        ${CMAKE_INSTALL_PREFIX}/lib/tinyxml2.lib
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


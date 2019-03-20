CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(ATApps)

link_directories(					
    ${CMAKE_INSTALL_PREFIX}/lib
)

include_directories(
    ${ATEXPLORER_ROOT}/source
    ${ATEXPLORER_ROOT}/source/core
    ${ATEXPLORER_ROOT}/source/atdata
    ${TP_INCLUDES}
    ${TP_INCLUDES}/dsl
    ${CMAKE_BINARY_DIR}/include    
)


if(INSTALL_APPS)
    add_subdirectory("ATCLI")
endif()




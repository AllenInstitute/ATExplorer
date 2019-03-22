CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(ATApps)

link_directories(					
    ${CMAKE_INSTALL_PREFIX}/lib
)

include_directories(
    ${ATEXPLORER_ROOT}/source
    ${ATEXPLORER_ROOT}/source/core
    ${ATEXPLORER_ROOT}/source/atdata
    ${ATEXPLORER_ROOT}/ThirdParty
    ${TP_INCLUDES}
    ${TP_INCLUDES}/dsl
)

link_directories(
    ${CMAKE_INSTALL_PREFIX}/lib
)

if(INSTALL_APPS)
    add_subdirectory("atcore")
endif()




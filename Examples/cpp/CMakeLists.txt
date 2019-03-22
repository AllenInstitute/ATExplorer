CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(ATExplorerExamples)

link_directories(					
    ${CMAKE_INSTALL_PREFIX}/lib
)

include_directories(
    /usr/local/include/dsl
    ${ATEXPLORER_ROOT}
    ${ATEXPLORER_ROOT}/Source
    ${ATEXPLORER_ROOT}/Source/core
    ${ATEXPLORER_ROOT}/Source/atdata
    ${CMAKE_SOURCE_DIR}/ThirdParties/Poco/Foundation/include
    ${CMAKE_INSTALL_PREFIX}/include
    ${CMAKE_INSTALL_PREFIX}/include/dsl
)

if(INSTALL_CXX_EXAMPLES)
    add_subdirectory("folder_iterator")
endif()




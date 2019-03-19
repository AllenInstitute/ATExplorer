cmake_minimum_required(VERSION 2.8)

set(target atcli)
PROJECT(${target})

include_directories(
    ${ATEXPLORER_ROOT}/source
    ${ATEXPLORER_ROOT}/source/core
    ${ATEXPLORER_ROOT}/source/atdata
    ${TP_INCLUDES}
    ${TP_INCLUDES}/dsl
)

set(src
main
atcli
atCLIUtils
)

if(CMAKE_SYSTEM MATCHES "Linux") 
    add_executable(${target} ${src})
else()
    add_executable(${target} ${src})
endif()
  
target_link_libraries(${target} 
atExplorerCore
atExplorerData
dslFoundation
        tinyxml2
        poco_foundation
        pthread
        -lrt
)

if(CMAKE_SYSTEM MATCHES "Linux") 
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
endif()

install(    
    TARGETS ${target} 	
    DESTINATION bin 
    COMPONENT apps
)
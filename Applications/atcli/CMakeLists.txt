cmake_minimum_required(VERSION 2.8)

set(target atcli)
PROJECT(${target})

set(src
main
atcore_class
atcore_utils
atcli
)

add_executable(${target} ${src})

if(CMAKE_SYSTEM MATCHES "Linux") 
    target_link_libraries(${target} 
    atExplorerCore
    atExplorerData
    dslFoundation
    tinyxml2
    poco_foundation
    pthread
    -lrt
    )

    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
endif()

install(    
    TARGETS ${target} 	
    DESTINATION bin 
    COMPONENT apps
)

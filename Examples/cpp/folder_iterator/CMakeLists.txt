cmake_minimum_required(VERSION 2.8)

set(target folder_iterator)
PROJECT(${target})

add_executable(${target} main.cpp)
  
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
    COMPONENT compiled_examples
)




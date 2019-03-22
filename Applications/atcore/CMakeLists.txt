cmake_minimum_required(VERSION 2.8)

set(target atcore)
PROJECT(${target})

set(src
main
atcore_class
atcore_utils
)

add_executable(${target} ${src})
  
target_link_libraries(${target} 
        atExplorerCore
        atExplorerData
#        dslFoundation
#        tinyxml2
#        poco_foundation
#        pthread
#        -lrt
)

if(CMAKE_SYSTEM_NAME MATCHES "Linux") 
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
elif(CMAKE_SYSTEM_NAME MATCHES "Windows")

endif()

install(    
    TARGETS ${target} 	
    DESTINATION bin 
    COMPONENT apps
)

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
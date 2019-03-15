cmake_minimum_required(VERSION 2.8)
project(ATExplorer)

SET(ATEXPLORER_MAJOR_VERSION 0)
SET(ATEXPLORER_MINOR_VERSION 5)
SET(ATEXPLORER_BUILD_VERSION 0)
SET(ATEXPLORER_VERSION "${ATEXPLORER_MAJOR_VERSION}.${ATEXPLORER_MINOR_VERSION}.${ATEXPLORER_BUILD_VERSION}")

set(ATEXPLORER_ROOT 	${CMAKE_CURRENT_SOURCE_DIR})
#mark_as_advanced(
#)

#Options
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )
endif()

OPTION(BUILD_SHARED_LIBS 		    "Build Shared Libs"                         ON)
OPTION(INSTALL_CXX_LIBS 		    "Install CXX libraries and headers"         ON)
OPTION(INSTALL_PYTHON 			    "Build Python Modules"                      OFF)
OPTION(INSTALL_CXX_EXAMPLES         "Install CXX Examples"	                    ON)
 
#Boost root
set(BOOST_ROOT  CACHE PATH "Directory containing Boost.")
if("${BOOST_ROOT}" STREQUAL "")
  set(BOOST_ROOT "C:/Borland" CACHE PATH "Directory containing Boost headers" FORCE)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/bin)

#=== COMPILER SPECIFICS 
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Embarcadero" AND ${CMAKE_BASE_NAME} STREQUAL "bcc32" )
    set(SUPPRESS_WARNINGS   "-w-8128 -w-8057 -w-8012 -w-8004 -w-8070" )
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release")
    message("Using bcc32")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Embarcadero" AND ${CMAKE_BASE_NAME} STREQUAL "bcc32c") 
    message("Using bcc32c")
#    set(SUPPRESS_WARNINGS "-Wunused-value")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(SUPPRESS_WARNINGS   "/wd4221 /wd4018 /wd4996 /wd4251" )
#    set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} /EHsc ")
#    set(CMAKE_CXX_MP_FLAG               ON CACHE BOOL "")
    add_definitions(
    -D_CRT_NONSTDC_NO_DEPRECATE
    -D_CRT_SECURE_NO_WARNINGS
    )
    message("Using MSVC")
else()
    message("No compiler!!" ${CMAKE_CXX_COMPILER_ID} ${CMAKE_BASE_NAME})
endif()

#Warning string looks different depending on the compiler..
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SUPPRESS_WARNINGS}")

set(TP_INCLUDES                     ${CMAKE_INSTALL_PREFIX}/include)
set(TP_LIBS                        ${CMAKE_INSTALL_PREFIX}/lib)

if(${INSTALL_PYTHON})
    OPTION(INSTALL_PYTHON_EXAMPLES  "Install Python Examples"	                 ON)
    find_package(PythonInterp)
    find_package(PythonLibs)
    message("Python include folder: " ${PYTHON_INCLUDE_DIRS})
    include_directories(
    ${PYTHON_INCLUDE_DIRS}
    )
    add_subdirectory(wrappers/python)
endif()    
 
include_directories(
${PYTHON_INCLUDE_DIRS}
${BOOST_ROOT}
${BOOST_ROOT}/boost/tr1/tr1
)
#Source Code Folders
add_subdirectory(source)
add_subdirectory(Examples)

#======================= INSTALL ========================================================
set(RootDest .)
install (FILES 
    README.txt 
    LICENSE.txt 
    AUTHORS.txt 
    VERSION.txt 
    INSTALL.txt 
    NOTICE.txt
    CHANGELOG.txt
    DESTINATION ${RootDest} 	
    COMPONENT info
   )


CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(atWrappers)

add_subdirectory("Source")

if(INSTALL_PYTHON)
    add_subdirectory("Wrappers")
endif()



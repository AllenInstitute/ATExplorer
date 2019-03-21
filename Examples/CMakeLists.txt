CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(DSLExamples)

if(INSTALL_CXX_EXAMPLES)
    add_subdirectory("cpp")
endif()

if(INSTALL_PYTHON_EXAMPLES)
    add_subdirectory("python")
endif()



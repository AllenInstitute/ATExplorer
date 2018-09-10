cmake_minimum_required(VERSION 2.8)
project(atexplorer)
find_package(PythonLibs)
get_filename_component(PYTHON_LIB_FOLDER ${PYTHON_LIBRARIES} DIRECTORY CACHE)
message("Python lib folder: "       ${PYTHON_LIB_FOLDER})
message("Python include folder: "   ${PYTHON_INCLUDE_DIRS})
message("Python libraries: "        ${PYTHON_LIBRARIES})

set(PyModule "atexplorer")

execute_process(COMMAND python -c "import site; print(site.getsitepackages()[1])" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
message("PYTHON_SITE_PACKAGES = ${PYTHON_SITE_PACKAGES}")

install(
    FILES         __init__.py 
                  utilities.py  
                  ${CMAKE_SOURCE_DIR}/VERSION.txt
    DESTINATION   ${PYTHON_SITE_PACKAGES}/${PyModule}
)

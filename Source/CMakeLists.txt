
INCLUDE_DIRECTORIES(
${ATEXPLORER_ROOT}
${ATEXPLORER_ROOT}/ThirdParty
${ATEXPLORER_ROOT}/source/core
${CG_BOOST_ROOT}
${TR1_ROOT}
${CMAKE_INSTALL_PREFIX}/include
${CMAKE_INSTALL_PREFIX}/include/dsl
)

add_subdirectory(core)
add_subdirectory(atdata)

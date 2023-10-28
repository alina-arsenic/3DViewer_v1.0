project(viewer C)
cmake_minimum_required(VERSION 3.22)

set(VIEWER_MAJOR_VERSION 0)
set(VIEWER_MINOR_VERSION 1)
set(VIEWER_PATCH_VERSION 0)
set(VIEWER_VERSION_STRING "${VIEWER_MAJOR_VERSION}.${VIEWER_MINOR_VERSION}.${VIEWER_PATCH_VERSION}")

set(VIEWER_BASE_DIR ${VIEWER_SOURCE_DIR})
set(VIEWER_AUTOGEN_DIR ${SVIEWER_BINARY_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/frontend ${CMAKE_SOURCE_DIR}/build/cmake_build/frontend)
#add_subdirectory(${CMAKE_SOURCE_DIR}/debug ${CMAKE_SOURCE_DIR}/build/cmake_build/debug)
#add_subdirectory(${CMAKE_SOURCE_DIR}/backend ${CMAKE_SOURCE_DIR}/build/cmake_build/backend_lib)
#add_subdirectory(${CMAKE_SOURCE_DIR}/tests ${CMAKE_SOURCE_DIR}/build/cmake_build/tests)
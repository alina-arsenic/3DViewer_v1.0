cmake_minimum_required(VERSION 3.22)

set (PROJECT_GUI gui)
project (${PROJECT_GUI} C)

# Including module
include(FindPkgConfig)

# Determine minimum C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER /usr/bin/gcc)

set(check_USE_STATIC_LIBS OFF)
set(check_USE_MULTITHREADED ON)

set(CMAKE_BUILD_TYPE Debug)

file(GLOB SRCS_GUI ../backend/*.c ./*.c)
file(GLOB HEAD_GUI ../backend/*.h ./*.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/materials
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(COMP_OPTIONS_GUI -Wall -Wextra -std=c11 -Wpedantic -Wno-unused-parameter -Wno-deprecated)
set(LINK_OPTIONS_GUI) # -export-dynamic -fsanitize=address -fsanitize=undefined)

#find_package(GTK REQUIRED gtk+-3.0)
pkg_check_modules(GTK REQUIRED gtk+-3.0)
pkg_check_modules(OGL REQUIRED gl)
pkg_check_modules(OGL REQUIRED glew)
#add_definitions(${GTK_LIBRARY_DIRS} ${OGL_LIBRARY_DIRS})
add_executable(${PROJECT_GUI} ${SRCS_GUI})

#find_package(slope REQUIRED static)

target_compile_options(${PROJECT_GUI} PRIVATE ${COMP_OPTIONS_GUI})
target_link_options(${PROJECT_GUI} PRIVATE ${LINK_OPTIONS_GUI})
target_link_libraries (${PROJECT_GUI} PRIVATE m ${GTK_LIBRARIES} ${OGL_LIBRARIES} ${GLEW_LIBRARIES})
target_link_directories(${PROJECT_GUI} PRIVATE ${GTK_LIBRARY_DIRS} ${OGL_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS})
target_include_directories(
        ${PROJECT_GUI}  PRIVATE
        ${GTK_INCLUDE_DIRS}
        ${OGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
)
set_target_properties(${PROJECT_GUI} PROPERTIES OUTPUT_NAME "viewer.app")
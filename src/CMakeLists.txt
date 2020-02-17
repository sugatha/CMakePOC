cmake_minimum_required(VERSION 3.12...3.16)

project(cmake_poc)

message (${CMAKE_CURRENT_SOURCE_DIR})
# Include the custom cmake common includes.
include (${CMAKE_CURRENT_SOURCE_DIR}/../common_cmake_includes/setup_configurations.cmake)
include (${CMAKE_CURRENT_SOURCE_DIR}/../common_cmake_includes/dependency-graph.cmake)

set(CMAKE_SHARED_LINKER_FLAGS_TEST "")

# to group the unwanted builds :)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set( CMAKE_POSITION_INDEPENDENT_CODE ON )

# This will help in making use of the ccache to speeden-up the compilation.
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

##################################################
message(STATUS "before calling prebuild - to generate the utillib")
prebuild()
message(STATUS "before calling prebuild - after generating utillib")
###################################################

# adding the subdirectories in this project - the sequence of including is important
add_subdirectory(utillib)
add_subdirectory(mylib_static)
add_subdirectory(mylib_shared)
add_subdirectory(theapp)


#generate the dependency graph
generate_graph(png)

add_dependencies(mylib_shared mylib_static)
add_dependencies(theapp mylib_shared)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT theapp)
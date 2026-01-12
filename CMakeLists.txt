cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(NAME midi_legend)
project(${NAME} VERSION 1.0)

option(BUILD_GUI "Build without console window (Windows only)" OFF)

message(STATUS "[INFO] Current directory: " ${CMAKE_SOURCE_DIR})

#-------------------------------------------------------------------------------
# Projects

add_subdirectory(application)

if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT application)
endif()

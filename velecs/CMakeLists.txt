# @file    CMakeLists.txt
# @author  Matthew Green
# @date    2023-11-30 13:49:39
# 
# @section LICENSE
# 
# Copyright (c) 2023 Matthew Green - All rights reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

cmake_minimum_required(VERSION 3.10)

project(velecs)

file(GLOB_RECURSE VELECS_SOURCES "src/*.cpp")
file(GLOB_RECURSE VELECS_HEADERS "include/*.h")

add_library(velecs ${VELECS_SOURCES} ${VELECS_HEADERS})

target_include_directories(velecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_precompile_headers(velecs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/velecs/pch.h")

# Get the absolute path to the root of your project
get_filename_component(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

# Use source_group with TREE to mirror directory structure
source_group(
    TREE "${ROOT_DIR}/include/velecs"
    PREFIX "Header Files"
    FILES ${VELECS_HEADERS}
)
source_group(
    TREE "${ROOT_DIR}/src/velecs"
    PREFIX "Source Files"
    FILES ${VELECS_SOURCES}
)
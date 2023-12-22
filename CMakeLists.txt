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

# Set the C++ standard for the velecs project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

add_subdirectory(libs)
add_subdirectory(assets)

file(GLOB_RECURSE VELECS_SOURCES "src/*.cpp")
file(GLOB_RECURSE VELECS_HEADERS "include/*.h")

add_library(velecs ${VELECS_SOURCES} ${VELECS_HEADERS})

target_include_directories(velecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_precompile_headers(velecs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/velecs/pch.h")

# Get the absolute path to the root of your project
get_filename_component(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

target_link_libraries(velecs
    Vulkan::Vulkan
    SDL2
    SDL2main
    glm
    vma
    flecs::flecs_static
    vk-bootstrap
    imgui
    assimp
)

# Add dependencies on custom asset targets
add_dependencies(velecs assets)

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
# @file    CMakeLists.txt
# @author  Matthew Green
# @date    2023-11-30 13:47:14
# 
# @section LICENSE
# 
# Copyright (c) 2023 Matthew Green - All rights reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0079 NEW)

project(HarvestHavoc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FINAL_OUTPUT_BASE_DIR "${CMAKE_SOURCE_DIR}/bin" CACHE PATH "Final output directory for executables and resources")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HarvestHavoc)

# Additional libs
add_subdirectory(libs)

add_subdirectory(velecs)
add_subdirectory(harvest_havoc)

find_package(Vulkan REQUIRED)

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

target_link_libraries(HarvestHavoc PRIVATE
    velecs
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

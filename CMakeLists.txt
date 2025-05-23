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

# Check if VULKAN_SDK is set
if(NOT DEFINED ENV{VULKAN_SDK})
    message(FATAL_ERROR "VULKAN_SDK environment variable is not set")
endif()

find_package(Vulkan REQUIRED)

# Set SDL2_DIR using VULKAN_SDK
# set(SDL2_DIR "$ENV{VULKAN_SDK}/Lib/cmake/SDL2")
# find_package(SDL2 REQUIRED)

add_subdirectory(libs)
# add_subdirectory(assets)

# Source files for the library
set(LIB_SOURCES
    src/Engine.cpp
)

# Header files for the library (for IDE organization)
set(LIB_HEADERS
    include/velecs/engine2/Engine.hpp
)

add_library(velecs-engine ${LIB_SOURCES} ${LIB_HEADERS})
# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(velecs-engine
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PUBLIC "$ENV{VULKAN_SDK}/Include"
)

target_link_libraries(velecs-engine
    PUBLIC velecs-math    
    PUBLIC SDL2
    PUBLIC SDL2main
)

# Export the library target for use by parent projects
if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # We're being included as a submodule
    set(VELECS_ENGINE_LIBRARIES velecs-engine PARENT_SCOPE)
endif()


# target_link_libraries(velecs
#     Vulkan::Vulkan
#     SDL2
#     SDL2main
#     glm
#     vma
#     assimp
#     flecs::flecs_static
#     imgui
#     stb
#     vk-bootstrap
# )

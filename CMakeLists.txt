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

add_subdirectory(libs)

# Source files for the library
set(LIB_SOURCES
    src/Engine.cpp
)

# Header files for the library (for IDE organization)
set(LIB_HEADERS
    include/velecs/engine/Engine.hpp
)

add_library(velecs-engine ${LIB_SOURCES} ${LIB_HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(velecs-engine
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(velecs-engine
    PUBLIC velecs-math
    # PUBLIC velecs-ecs
    PUBLIC velecs-input
    PUBLIC SDL3
)

# Export the library target for use by parent projects
if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # We're being included as a submodule
    set(VELECS_ENGINE_LIBRARIES velecs-engine PARENT_SCOPE)
endif()

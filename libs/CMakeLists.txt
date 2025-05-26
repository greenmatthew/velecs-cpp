# @file    CMakeLists.txt
# @author  Matthew Green
# @date    2023-11-30 13:48:34
# 
# @section LICENSE
# 
# Copyright (c) 2023 Matthew Green - All rights reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

cmake_minimum_required(VERSION 3.10)

##############################################################################################
### velecs-X #################################################################################
##############################################################################################

# Ordered considering dependencies...
add_subdirectory(velecs-math)
add_subdirectory(velecs-ecs) # depends on velecs-math
add_subdirectory(velecs-input) # depends on velecs-math

##############################################################################################
### !velecs-X ################################################################################
##############################################################################################



##############################################################################################
### SDL2 #####################################################################################
##############################################################################################

if(NOT DEFINED ENV{VULKAN_SDK})
    message(FATAL_ERROR "VULKAN_SDK environment variable is not set")
endif()

set(VULKAN_SDK $ENV{VULKAN_SDK})

# Create imported targets for SDL2 with all build configurations
add_library(SDL2 STATIC IMPORTED GLOBAL)
set_target_properties(SDL2 PROPERTIES
    IMPORTED_LOCATION_DEBUG "${VULKAN_SDK}/Lib/SDL2d.lib"
    IMPORTED_LOCATION_RELEASE "${VULKAN_SDK}/Lib/SDL2.lib"
    IMPORTED_LOCATION_MINSIZEREL "${VULKAN_SDK}/Lib/SDL2.lib"
    IMPORTED_LOCATION_RELWITHDEBINFO "${VULKAN_SDK}/Lib/SDL2.lib"
)

add_library(SDL2main STATIC IMPORTED GLOBAL)
set_target_properties(SDL2main PROPERTIES
    IMPORTED_LOCATION_DEBUG "${VULKAN_SDK}/Lib/SDL2maind.lib"
    IMPORTED_LOCATION_RELEASE "${VULKAN_SDK}/Lib/SDL2main.lib"
    IMPORTED_LOCATION_MINSIZEREL "${VULKAN_SDK}/Lib/SDL2main.lib"
    IMPORTED_LOCATION_RELWITHDEBINFO "${VULKAN_SDK}/Lib/SDL2main.lib"
)

# Create a convenience target that combines both
add_library(SDL2-all INTERFACE)
target_link_libraries(SDL2-all INTERFACE SDL2 SDL2main)
target_include_directories(SDL2-all INTERFACE "${VULKAN_SDK}/Include/SDL2")

##############################################################################################
### !SDL2 ####################################################################################
##############################################################################################

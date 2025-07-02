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

##############################################################################################
### SDL3 #####################################################################################
##############################################################################################

# Add SDL3 as a subdirectory (it's a git submodule)
# Configure SDL3 options before adding the subdirectory

# Build configuration
set(SDL_SHARED OFF CACHE BOOL "Build SDL3 as shared library")
set(SDL_STATIC ON CACHE BOOL "Build SDL3 as static library") 
set(SDL_TEST_LIBRARY OFF CACHE BOOL "Build SDL3 test library")
set(SDL_TESTS OFF CACHE BOOL "Build SDL3 tests")
set(SDL_EXAMPLES OFF CACHE BOOL "Build SDL3 examples")
set(SDL_INSTALL OFF CACHE BOOL "Disable SDL3 installation")

# Core subsystems we need
set(SDL_AUDIO ON CACHE BOOL "Enable Audio subsystem")
set(SDL_VIDEO ON CACHE BOOL "Enable Video subsystem") 
set(SDL_GPU OFF CACHE BOOL "Enable GPU subsystem")
set(SDL_RENDER OFF CACHE BOOL "Enable Render subsystem")
set(SDL_CAMERA OFF CACHE BOOL "Disable Camera subsystem")
set(SDL_JOYSTICK ON CACHE BOOL "Enable Joystick subsystem")
set(SDL_HAPTIC ON CACHE BOOL "Enable Haptic subsystem")
set(SDL_HIDAPI ON CACHE BOOL "Enable HIDAPI subsystem")
set(SDL_POWER ON CACHE BOOL "Enable Power subsystem")
set(SDL_SENSOR ON CACHE BOOL "Enable Sensor subsystem")
set(SDL_DIALOG ON CACHE BOOL "Disable Dialog subsystem")

# Add SDL3 subdirectory
# add_subdirectory(SDL)

# add_library(SDL3 INTERFACE)
# target_link_libraries(SDL3 INTERFACE SDL3::SDL3)

##############################################################################################
### !SDL3 ####################################################################################
##############################################################################################

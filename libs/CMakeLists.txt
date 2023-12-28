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

# Assuming VULKAN_SDK environment variable is set to the root of the Vulkan SDK
set(VULKAN_SDK $ENV{VULKAN_SDK})

find_package(Vulkan REQUIRED)

add_library(glm INTERFACE)
target_compile_definitions(glm INTERFACE GLM_FORCE_DEPTH_ZERO_TO_ONE)

add_library(vma INTERFACE)


# SDL2
# Create a static library target for SDL2 using the provided static libs
add_library(SDL2 STATIC IMPORTED GLOBAL)
set_target_properties(SDL2 PROPERTIES
  IMPORTED_LOCATION "${VULKAN_SDK}/Lib/SDL2.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${VULKAN_SDK}/Include/SDL2"
)

# SDL2main
# Create a static library target for SDL2main
add_library(SDL2main STATIC IMPORTED GLOBAL)
set_target_properties(SDL2main PROPERTIES
  IMPORTED_LOCATION "${VULKAN_SDK}/Lib/SDL2main.lib"
)

##############################################################################################
### Libs using Git submodules: ###############################################################
##############################################################################################

#---------------------------------------------------------------------------------------------
#-- ASSIMP -----------------------------------------------------------------------------------
#---------------------------------------------------------------------------------------------
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build package with shared libraries.")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "If the test suite for Assimp is built in addition to the library.")
set(ASSIMP_INSTALL OFF CACHE BOOL "Disable Assimp install.")

add_subdirectory(assimp)



#---------------------------------------------------------------------------------------------
#-- FLECS ------------------------------------------------------------------------------------
#---------------------------------------------------------------------------------------------
set(FLECS_STATIC ON CACHE BOOL "Build static flecs lib")
set(FLECS_SHARED OFF CACHE BOOL "Build shared flecs lib")
set(FLECS_PIC ON CACHE BOOL "Compile static flecs lib with position independent code (PIC)")
set(FLECS_TESTS OFF CACHE BOOL "Build flecs tests")
add_subdirectory(flecs)



#---------------------------------------------------------------------------------------------
#-- Dear ImGui -------------------------------------------------------------------------------
#---------------------------------------------------------------------------------------------
add_library(imgui STATIC)
target_include_directories(imgui PUBLIC imgui)
target_sources(imgui PRIVATE 
    imgui/imgui.h
    imgui/imgui.cpp

    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp

    imgui/backends/imgui_impl_vulkan.cpp
    imgui/backends/imgui_impl_sdl2.cpp
)
target_link_libraries(imgui PUBLIC Vulkan::Vulkan SDL2 SDL2main)



#---------------------------------------------------------------------------------------------
#-- stb --------------------------------------------------------------------------------------
#---------------------------------------------------------------------------------------------
add_library(stb INTERFACE)
target_sources(stb PRIVATE
    stb/stb_image.h
    stb/stb_perlin.h
    stb/stb_truetype.h
    stb/stb_image_write.h
)
target_include_directories(stb INTERFACE stb)



#---------------------------------------------------------------------------------------------
#-- vkbootstrap ------------------------------------------------------------------------------
#---------------------------------------------------------------------------------------------
set(VK_BOOTSTRAP_DISABLE_WARNINGS OFF CACHE BOOL "Disable warnings during compilation")
set(VK_BOOTSTRAP_WERROR OFF CACHE BOOL "Enable warnings as errors during compilation")
add_subdirectory(vkbootstrap)

cmake_minimum_required(VERSION 3.10)

# Assuming VULKAN_SDK environment variable is set to the root of the Vulkan SDK
set(VULKAN_SDK $ENV{VULKAN_SDK})

find_package(Vulkan REQUIRED)

add_library(imgui STATIC)
add_library(vkbootstrap STATIC)
add_library(glm INTERFACE)
add_library(vma INTERFACE)
add_library(tiny_obj_loader INTERFACE)

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

# flecs
set(FLECS_STATIC ON CACHE BOOL "Build static flecs lib")
set(FLECS_SHARED OFF CACHE BOOL "Build shared flecs lib")
set(FLECS_PIC ON CACHE BOOL "Compile static flecs lib with position independent code (PIC)")
set(FLECS_TESTS OFF CACHE BOOL "Build flecs tests")
add_subdirectory(flecs)

# imgui
target_include_directories(imgui PUBLIC imgui)
target_sources(imgui PRIVATE 
    imgui/imgui.h
    imgui/imgui.cpp

    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp

    imgui/backends/imgui_impl_vulkan.cpp
    imgui/backends/imgui_impl_sdl2.cpp
)
target_link_libraries(imgui PUBLIC Vulkan::Vulkan SDL2 SDL2main)

# vkbootstrap
target_sources(vkbootstrap PRIVATE 
    vkbootstrap/VkBootstrap.h
    vkbootstrap/VkBootstrap.cpp
)
target_include_directories(vkbootstrap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(vkbootstrap PUBLIC Vulkan::Vulkan $<$<BOOL:UNIX>:${CMAKE_DL_LIBS}>)

# tiny_obj_loader (header only)
target_include_directories(tiny_obj_loader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

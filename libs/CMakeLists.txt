cmake_minimum_required(VERSION 3.10)

# Assuming VULKAN_SDK environment variable is set to the root of the Vulkan SDK
set(VULKAN_SDK $ENV{VULKAN_SDK})

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
file(GLOB FLECS_SOURCES "flecs/*.c" "flecs/*.h")
add_library(flecs STATIC ${FLECS_SOURCES})
target_include_directories(flecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# imgui
file(GLOB IMGUI_SOURCES "imgui/*.h" "imgui/*.cpp")
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# vkbootstrap
file(GLOB VKBOOTSTRAP_SOURCES "vkbootstrap/*.h" "vkbootstrap/*.cpp")
add_library(vkbootstrap STATIC ${VKBOOTSTRAP_SOURCES})
target_include_directories(vkbootstrap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# tiny_obj_loader (header only)
file(GLOB TINY_OBJ_LOADER_SOURCES "tiny_obj_loader/*.h")
add_library(tiny_obj_loader INTERFACE ${TINY_OBJ_LOADER_SOURCES})
target_include_directories(tiny_obj_loader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

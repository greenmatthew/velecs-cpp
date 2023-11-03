cmake_minimum_required(VERSION 3.10)

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

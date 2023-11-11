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
    flecs_static
    vk-bootstrap
    imgui
    tiny_obj_loader
)

target_link_libraries(HarvestHavoc PRIVATE
    velecs
    Vulkan::Vulkan
    SDL2
    SDL2main
    flecs_static
    vk-bootstrap
    imgui
    tiny_obj_loader
)

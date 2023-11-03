cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0079 NEW)

project(velecs)
# project(harvest_havoc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Additional libs
add_subdirectory(libs)

add_subdirectory(velecs)
# add_subdirectory(harvest_havoc)

find_package(Vulkan REQUIRED)

target_link_libraries(vkbootstrap Vulkan::Vulkan)
target_link_libraries(imgui Vulkan::Vulkan)
target_link_libraries(velecs Vulkan::Vulkan flecs vkbootstrap imgui tiny_obj_loader)
# target_link_libraries(harvest_havoc Vulkan::Vulkan flecs vkbootstrap imgui tiny_obj_loader)

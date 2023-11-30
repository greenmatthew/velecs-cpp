# @file    CMakeLists.txt
# @author  Matthew Green
# @date    2023-11-30 13:49:11
# 
# @section LICENSE
# 
# Copyright (c) 2023 Matthew Green - All rights reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

cmake_minimum_required(VERSION 3.10)

# Find the Vulkan shader compiler
find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)

# Define shader source directories
set(VERTEX_SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vert")
set(FRAGMENT_SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/frag")

# Find all the vertex and fragment shader files
file(GLOB_RECURSE VERTEX_SHADERS "${VERTEX_SHADER_DIR}/*.vert")
file(GLOB_RECURSE FRAGMENT_SHADERS "${FRAGMENT_SHADER_DIR}/*.frag")

# Create a list to hold the output SPIR-V files
set(SPIRV_BINARY_FILES "")

foreach(GLSL ${VERTEX_SHADERS} ${FRAGMENT_SHADERS})
  get_filename_component(FILE_NAME_WITH_EXT ${GLSL} NAME)
  get_filename_component(PARENT_DIR ${GLSL} DIRECTORY)
  get_filename_component(LAST_DIR_NAME ${PARENT_DIR} NAME)
  
  # Output path including the build configuration and the lowest level directory
  set(SPIRV "${FINAL_OUTPUT_BASE_DIR}/$<CONFIG>/assets/shaders/${LAST_DIR_NAME}/${FILE_NAME_WITH_EXT}.spv")
  
  # Add custom command to compile the shader
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${FINAL_OUTPUT_BASE_DIR}/$<CONFIG>/assets/shaders/${LAST_DIR_NAME}"
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL}
    COMMENT "Compiling ${GLSL} to SPIR-V"
    VERBATIM
  )
  
  # Append the SPIR-V file to the list
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach()

# Add custom target that depends on all SPIR-V files
add_custom_target(shaders ALL DEPENDS ${SPIRV_BINARY_FILES})

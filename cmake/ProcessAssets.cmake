# @file    ProcessAssets.cmake
# @author  Matthew Green
# @date    2025-07-13 12:45:09
# 
# @section LICENSE
# 
# Copyright (c) 2025 Matthew Green - All rights reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

cmake_minimum_required(VERSION 3.16)

# Find shader compilers - prefer glslc, fallback to glslangValidator
find_program(GLSLC_EXECUTABLE glslc HINTS 
    $ENV{VULKAN_SDK}/Bin 
    $ENV{VULKAN_SDK}/Bin32
    /usr/bin 
    /usr/local/bin
)

find_program(GLSLANG_VALIDATOR glslangValidator HINTS 
    $ENV{VULKAN_SDK}/Bin 
    $ENV{VULKAN_SDK}/Bin32
    /usr/bin 
    /usr/local/bin
)

if(GLSLC_EXECUTABLE)
    set(SHADER_COMPILER ${GLSLC_EXECUTABLE})
    set(SHADER_COMPILER_TYPE "glslc")
    message(STATUS "Found glslc: ${GLSLC_EXECUTABLE}")
elseif(GLSLANG_VALIDATOR)
    set(SHADER_COMPILER ${GLSLANG_VALIDATOR})
    set(SHADER_COMPILER_TYPE "glslangValidator")
    message(STATUS "Found glslangValidator: ${GLSLANG_VALIDATOR}")
else()
    message(FATAL_ERROR "No shader compiler found! Install Vulkan SDK.")
endif()

set(ASSET_DEBUG_MODE OFF CACHE BOOL "Enable asset processing debug messages")

set(SHADER_EXTENSIONS 
    ".vert" ".frag" ".geom" ".comp" 
    ".tesc" ".tese" ".rgen" ".rmiss" 
    ".rchit" ".rahit" ".rint" ".rcall"
)

function(asset_debug_message MESSAGE)
    if(ASSET_DEBUG_MODE)
        message(STATUS "[AssetDebug] ${MESSAGE}")
    endif()
endfunction()

function(is_shader_file FILE_PATH RESULT)
    get_filename_component(FILE_EXT "${FILE_PATH}" LAST_EXT)
    set(${RESULT} FALSE PARENT_SCOPE)
    
    foreach(SHADER_EXT IN LISTS SHADER_EXTENSIONS)
        if(FILE_EXT STREQUAL SHADER_EXT)
            set(${RESULT} TRUE PARENT_SCOPE)
            break()
        endif()
    endforeach()
endfunction()

# Create a comprehensive asset processing script
function(create_asset_processing_script TARGET_NAME)
    set(SCRIPT_FILE "${CMAKE_CURRENT_BINARY_DIR}/process_assets_${TARGET_NAME}.cmake")
    
    # Start writing the script
    file(WRITE "${SCRIPT_FILE}" "
# Asset processing script for ${TARGET_NAME}
set(SHADER_COMPILER \"${SHADER_COMPILER}\")
set(SHADER_COMPILER_TYPE \"${SHADER_COMPILER_TYPE}\")

# Function to ensure directory exists
function(ensure_directory DIR)
    if(NOT EXISTS \"\${DIR}\")
        file(MAKE_DIRECTORY \"\${DIR}\")
    endif()
endfunction()

# Function to copy an asset
function(copy_asset SOURCE DEST REL_PATH)
    get_filename_component(DEST_DIR \"\${DEST}\" DIRECTORY)
    ensure_directory(\"\${DEST_DIR}\")
    execute_process(
        COMMAND \"\${CMAKE_COMMAND}\" -E copy_if_different \"\${SOURCE}\" \"\${DEST}\"
        RESULT_VARIABLE RESULT
    )
    if(NOT RESULT EQUAL 0)
        message(FATAL_ERROR \"Failed to copy asset: \${REL_PATH}\")
    endif()
endfunction()

# Function to compile a shader
function(compile_shader SOURCE DEST REL_PATH)
    get_filename_component(DEST_DIR \"\${DEST}\" DIRECTORY)
    ensure_directory(\"\${DEST_DIR}\")
    
    if(SHADER_COMPILER_TYPE STREQUAL \"glslc\")
        execute_process(
            COMMAND \"\${SHADER_COMPILER}\" \"\${SOURCE}\" -o \"\${DEST}\"
            RESULT_VARIABLE RESULT
        )
    else()
        execute_process(
            COMMAND \"\${SHADER_COMPILER}\" -V \"\${SOURCE}\" -o \"\${DEST}\"
            RESULT_VARIABLE RESULT
        )
    endif()
    
    if(NOT RESULT EQUAL 0)
        message(FATAL_ERROR \"Failed to compile shader: \${REL_PATH}\")
    endif()
endfunction()

message(\"\")
message(\"Asset processing post-build step:\")
")

    # Return the script file path
    set(ASSET_SCRIPT_FILE "${SCRIPT_FILE}" PARENT_SCOPE)
endfunction()

# Process assets from a specific directory and add to script
function(add_assets_to_script TARGET_NAME ASSETS_DIR NAMESPACE SCRIPT_FILE)
    if(NOT EXISTS "${ASSETS_DIR}")
        return()
    endif()
    
    file(GLOB_RECURSE ALL_ASSET_FILES "${ASSETS_DIR}/*")
    
    # Separate shaders and regular assets
    set(SHADER_FILES "")
    set(REGULAR_FILES "")
    
    foreach(ASSET_FILE IN LISTS ALL_ASSET_FILES)
        if(IS_DIRECTORY "${ASSET_FILE}")
            continue()
        endif()
        
        file(RELATIVE_PATH REL_PATH "${ASSETS_DIR}" "${ASSET_FILE}")
        is_shader_file("${ASSET_FILE}" IS_SHADER)
        
        if(IS_SHADER)
            list(APPEND SHADER_FILES "${REL_PATH}")
        else()
            list(APPEND REGULAR_FILES "${REL_PATH}")
        endif()
    endforeach()
    
    # Add to script if we have files
    if(SHADER_FILES OR REGULAR_FILES)
        # Sort the lists
        if(SHADER_FILES)
            list(SORT SHADER_FILES)
        endif()
        if(REGULAR_FILES)
            list(SORT REGULAR_FILES)
        endif()
        
        # Create the output directory path - empty for game assets, namespace for engine assets
        if(NAMESPACE STREQUAL "")
            set(OUTPUT_DIR "")
            set(DISPLAY_NAME "game")
        else()
            set(OUTPUT_DIR "${NAMESPACE}/")
            set(DISPLAY_NAME "${NAMESPACE}")
        endif()
        
        file(APPEND "${SCRIPT_FILE}" "
message(\"  ${DISPLAY_NAME} assets:\")
")
        
        # Add shader compilation section
        if(SHADER_FILES)
            file(APPEND "${SCRIPT_FILE}" "
message(\"    Compiling shaders:\")
")
            foreach(SHADER_REL_PATH IN LISTS SHADER_FILES)
                set(SOURCE_FILE "${ASSETS_DIR}/${SHADER_REL_PATH}")
                file(APPEND "${SCRIPT_FILE}" "
message(\"      ${SHADER_REL_PATH} -> ${SHADER_REL_PATH}.spv\")
compile_shader(\"${SOURCE_FILE}\" \"\${TARGET_FILE_DIR}/assets/${OUTPUT_DIR}${SHADER_REL_PATH}.spv\" \"${SHADER_REL_PATH}\")
")
            endforeach()
        endif()
        
        # Add regular asset copying section
        if(REGULAR_FILES)
            file(APPEND "${SCRIPT_FILE}" "
message(\"    Copying assets:\")
")
            foreach(ASSET_REL_PATH IN LISTS REGULAR_FILES)
                set(SOURCE_FILE "${ASSETS_DIR}/${ASSET_REL_PATH}")
                file(APPEND "${SCRIPT_FILE}" "
message(\"      ${ASSET_REL_PATH}\")
copy_asset(\"${SOURCE_FILE}\" \"\${TARGET_FILE_DIR}/assets/${OUTPUT_DIR}${ASSET_REL_PATH}\" \"${ASSET_REL_PATH}\")
")
            endforeach()
        endif()
        
        # Count for logging
        list(LENGTH SHADER_FILES SHADER_COUNT)
        list(LENGTH REGULAR_FILES ASSET_COUNT)
        math(EXPR TOTAL_COUNT "${SHADER_COUNT} + ${ASSET_COUNT}")
        
        set(PROCESSED_COUNT_${NAMESPACE} ${TOTAL_COUNT} PARENT_SCOPE)
    endif()
endfunction()

# Main function to setup asset pipeline using a single organized POST_BUILD step
function(setup_asset_pipeline TARGET_NAME)
    # Create the processing script
    create_asset_processing_script(${TARGET_NAME})
    
    # Add engine assets with "internal" namespace
    set(ENGINE_ASSETS_DIR "${CMAKE_SOURCE_DIR}/libs/velecs/assets")
    if(EXISTS "${ENGINE_ASSETS_DIR}")
        add_assets_to_script(${TARGET_NAME} "${ENGINE_ASSETS_DIR}" "internal" "${ASSET_SCRIPT_FILE}")
    endif()
    
    # Add game assets with empty namespace (goes directly to assets root)
    set(GAME_ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
    if(EXISTS "${GAME_ASSETS_DIR}")
        add_assets_to_script(${TARGET_NAME} "${GAME_ASSETS_DIR}" "" "${ASSET_SCRIPT_FILE}")
    endif()
    
    # Finish the script
    file(APPEND "${ASSET_SCRIPT_FILE}" "
message(\"\")
")
    
    # Add single POST_BUILD command that runs our organized script
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} 
            -DTARGET_FILE_DIR=$<TARGET_FILE_DIR:${TARGET_NAME}>
            -P "${ASSET_SCRIPT_FILE}"
        COMMENT "Processing assets for ${TARGET_NAME}"
        VERBATIM
    )
    
    # Log what we registered during configure
    set(TOTAL_REGISTERED 0)
    if(DEFINED PROCESSED_COUNT_internal)
        math(EXPR TOTAL_REGISTERED "${TOTAL_REGISTERED} + ${PROCESSED_COUNT_internal}")
        message(STATUS "Registered ${PROCESSED_COUNT_internal} engine assets for processing")
    endif()
    if(DEFINED PROCESSED_COUNT_)
        math(EXPR TOTAL_REGISTERED "${TOTAL_REGISTERED} + ${PROCESSED_COUNT_}")
        message(STATUS "Registered ${PROCESSED_COUNT_} game assets for processing")
    endif()
endfunction()

# Convenience function (same name as before for compatibility)
function(setup_assets TARGET_NAME)
    setup_asset_pipeline(${TARGET_NAME})
endfunction()

# @file    AssetUtility.cmake
# @author  Matthew Green
# @date    2023-12-22 20:03:29
# 
# @section LICENSE
# 
# Copyright (c) 2023 Matthew Green - All rights reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

cmake_minimum_required(VERSION 3.10)

find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)

set(DEBUG_MODE OFF)  # Set to ON to enable debug messages or OFF to disable debug messages



function(debug_message MESSAGE)
    if(DEBUG_MODE)
        message(STATUS "[Debug][Assets] ${MESSAGE}")
    endif()
endfunction()



# Function to check if a file matches any of the given ignore patterns
function(matches_ignore_pattern FILE IGNORE_PATTERNS MATCH_RESULT)
    set(RESULT FALSE)
    foreach(IGNORE_PATTERN IN LISTS IGNORE_PATTERNS)
        # Convert glob patterns to regular expressions
        string(REPLACE "*" ".*" REGEX_PATTERN "${IGNORE_PATTERN}")
        string(REPLACE "?" "." REGEX_PATTERN "${REGEX_PATTERN}")
        if(FILE MATCHES "${REGEX_PATTERN}")
            set(RESULT TRUE)
            break()  # No need to check other ignore patterns
        endif()
    endforeach()

    # Set the result in the parent scope
    set(${MATCH_RESULT} ${RESULT} PARENT_SCOPE)
endfunction()



function(list_all_files DIR FILE_LIST IGNORE_PATTERNS)
    set(LOCAL_FILE_LIST ${${FILE_LIST}})  # Initialize with the current file list
    
    file(GLOB_RECURSE TEMP_FILES "${DIR}/*")
    foreach(FILE ${TEMP_FILES})
        if(NOT IS_DIRECTORY ${FILE})
            # Check if the file should be ignored
            set(SHOULD_IGNORE FALSE)
            matches_ignore_pattern("${FILE}" "${IGNORE_PATTERNS}" SHOULD_IGNORE)

            if(SHOULD_IGNORE)
                debug_message("Ignoring file: ${FILE}")
            else()
                list(APPEND LOCAL_FILE_LIST ${FILE})
            endif()
        endif()
    endforeach()

    # Set the updated file list in the parent scope
    set(${FILE_LIST} ${LOCAL_FILE_LIST} PARENT_SCOPE)
endfunction()



function(process_single_file_to_relative_destination SOURCE_FILE ASSETS_DIR DEST_DIR COPIED_FILE)
    get_filename_component(PARENT_DIR "${SOURCE_FILE}" DIRECTORY)
    file(RELATIVE_PATH RELATIVE_DIR ${ASSETS_DIR} ${PARENT_DIR})
    get_filename_component(FILE_NAME "${SOURCE_FILE}" NAME)
    get_filename_component(FILE_EXT "${FILE}" LAST_EXT)

    # Output path including the build configuration
    set(OUTPUT_DIR ${DEST_DIR}/${RELATIVE_DIR})
    set(OUTPUT_FILE "${DEST_DIR}/${RELATIVE_DIR}/${FILE_NAME}")

    debug_message("FILE_EXT: ${FILE_EXT}")

    if (${FILE_EXT} MATCHES ".vert" OR ${FILE_EXT} MATCHES  ".frag")
        set(OUTPUT_FILE "${OUTPUT_FILE}.spv")
        debug_message("Preparing to compile: ${SOURCE_FILE} to ${OUTPUT_FILE}")

        add_custom_command(
            OUTPUT ${OUTPUT_FILE}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_DIR}"
            COMMAND ${GLSL_VALIDATOR} -V ${SOURCE_FILE} -o ${OUTPUT_FILE}
            DEPENDS ${SOURCE_FILE}
            COMMENT "Compiling ${SOURCE_FILE} to SPIR-V"
            VERBATIM
        )
    else()
        debug_message("Preparing to copy: ${SOURCE_FILE} to ${OUTPUT_FILE}")

        # Add custom command to copy the asset
        add_custom_command(
            OUTPUT ${OUTPUT_FILE}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SOURCE_FILE}" "${OUTPUT_FILE}"
            DEPENDS "${SOURCE_FILE}"
            COMMENT "Copying ${SOURCE_FILE} to ${OUTPUT_FILE}"
            VERBATIM
        )
    endif()

    # Set the copied file's path in the parent scope
    set(${COPIED_FILE} ${OUTPUT_FILE} PARENT_SCOPE)
endfunction()



function(process_files_to_relative_destination FILES ASSETS_DIR DEST_DIR COPIED_FILES_LIST)
    set(LOCAL_COPIED_FILES "")

    foreach (FILE IN LISTS FILES)
        # Call the function to copy a single file
        set(SINGLE_COPIED_FILE "")
        process_single_file_to_relative_destination("${FILE}" "${ASSETS_DIR}" "${DEST_DIR}" SINGLE_COPIED_FILE)

        # Append the copied asset file to the local list
        list(APPEND LOCAL_COPIED_FILES ${SINGLE_COPIED_FILE})
    endforeach()

    # Update the list in the parent scope
    set(${COPIED_FILES_LIST} ${LOCAL_COPIED_FILES} PARENT_SCOPE)
endfunction()



function(process_assets ASSETS_DIR DEST_DIR PATHS_TO_IGNORE COPIED_FILES_LIST)
    # Automatically find all subdirectories and files in the assets directory
    file(GLOB ASSET_PATHS LIST_DIRECTORIES true RELATIVE ${ASSETS_DIR} "${ASSETS_DIR}/*")
    set(ALL_ASSET_FILES "")
    set(LOCAL_COPIED_FILES "")

    # Iterate over each path in the assets directory
    foreach(PATH IN LISTS ASSET_PATHS)
        set(FULL_PATH "${ASSETS_DIR}/${PATH}")
        if(EXISTS ${FULL_PATH})
            if(IS_DIRECTORY ${FULL_PATH})
                set(SUBDIR ${PATH})
                debug_message("Checking directory: ${SUBDIR}")
                
                list_all_files("${FULL_PATH}" "ALL_ASSET_FILES" "${PATHS_TO_IGNORE}")
            else()
                debug_message("Checking file: ${FULL_PATH}")

                # Determine if the file should be ignored
                set(SHOULD_IGNORE FALSE)
                matches_ignore_pattern("${FULL_PATH}" "${PATHS_TO_IGNORE}" SHOULD_IGNORE)

                if(SHOULD_IGNORE)
                    debug_message(STATUS "Ignoring file: ${FULL_PATH}")
                else()
                    # If the file is not ignored, process it for copying
                    list(APPEND ALL_ASSET_FILES ${FULL_PATH})
                endif()
            endif()
        endif()
    endforeach()

    debug_message("ALL_ASSET_FILES: ${ALL_ASSET_FILES}")  # Ensure this shows the expected files

    # After processing all paths, copy the files to the destination
    process_files_to_relative_destination("${ALL_ASSET_FILES}" "${ASSETS_DIR}" "${DEST_DIR}" LOCAL_COPIED_FILES)
    set(${COPIED_FILES_LIST} ${LOCAL_COPIED_FILES} PARENT_SCOPE)
endfunction()
cmake_minimum_required(VERSION 3.10)

# Define the meshes source directory
set(MESHES_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# List of mesh file extensions to copy
set(MESH_FILE_EXTENSIONS
    "obj"
    "fbx"
    # Add more extensions as needed
)  

# Create a list to hold all mesh files across all extensions
set(MESH_FILES "")

# Iterate over each file extension and collect files
foreach(EXTENSION ${MESH_FILE_EXTENSIONS})
    file(GLOB_RECURSE FOUND_FILES "${MESHES_DIR}/*.${EXTENSION}")
    list(APPEND MESH_FILES ${FOUND_FILES})
endforeach()

# Create a list to hold the output paths for the copied mesh files
set(COPIED_MESH_FILES "")

foreach(MESH ${MESH_FILES})
    get_filename_component(FILE_NAME ${MESH} NAME)
    get_filename_component(PARENT_DIR ${MESH} DIRECTORY)
    file(RELATIVE_PATH RELATIVE_DIR ${MESHES_DIR} ${PARENT_DIR})

    # Output path including the build configuration
    set(OUTPUT_MESH "${FINAL_OUTPUT_BASE_DIR}/$<CONFIG>/assets/meshes/${RELATIVE_DIR}/${FILE_NAME}")

    # Add custom command to copy the mesh
    add_custom_command(
        OUTPUT ${OUTPUT_MESH}
        COMMAND ${CMAKE_COMMAND} -E make_directory "${FINAL_OUTPUT_BASE_DIR}/$<CONFIG>/assets/meshes/${RELATIVE_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy ${MESH} ${OUTPUT_MESH}
        DEPENDS ${MESH}
        COMMENT "Copying ${MESH} to ${OUTPUT_MESH}"
        VERBATIM
    )

    # Append the copied mesh file to the list
    list(APPEND COPIED_MESH_FILES ${OUTPUT_MESH})
endforeach()

# Add custom target that depends on all copied mesh files
add_custom_target(meshes ALL DEPENDS ${COPIED_MESH_FILES})

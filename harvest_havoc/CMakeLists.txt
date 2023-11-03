project(harvest_havoc)

file(GLOB_RECURSE HARVEST_HAVOC_HEADERS "include/*.h")
file(GLOB_RECURSE HARVEST_HAVOC_SOURCES "src/*.cpp")

add_library(harvest_havoc ${HARVEST_HAVOC_SOURCES} ${HARVEST_HAVOC_HEADERS})

add_dependencies(harvest_havoc velecs)

target_include_directories(harvest_havoc PUBLIC include)

# Get the absolute path to the root of your project
get_filename_component(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

# Use source_group with TREE to mirror directory structure
source_group(
    TREE "${ROOT_DIR}/include"
    PREFIX "Header Files"
    FILES ${VELECS_HEADERS}
)
source_group(
    TREE "${ROOT_DIR}/src"
    PREFIX "Source Files"
    FILES ${VELECS_SOURCES}
)
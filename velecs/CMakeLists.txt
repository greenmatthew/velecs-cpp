project(velecs)

file(GLOB_RECURSE VELECS_SOURCES "src/*.cpp")
file(GLOB_RECURSE VELECS_HEADERS "include/*.h")

add_library(velecs ${VELECS_SOURCES} ${VELECS_HEADERS})

target_include_directories(velecs PUBLIC include)

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
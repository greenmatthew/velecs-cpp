file(GLOB_RECURSE HARVEST_HAVOC_HEADERS "include/*.h")
file(GLOB_RECURSE HARVEST_HAVOC_SOURCES "src/*.cpp")

add_executable(HarvestHavoc ${HARVEST_HAVOC_SOURCES} ${HARVEST_HAVOC_HEADERS})

set_target_properties(HarvestHavoc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${FINAL_OUTPUT_BASE_DIR}/$<CONFIG>"
)

add_dependencies(HarvestHavoc velecs)

target_include_directories(HarvestHavoc PUBLIC include)

# Get the absolute path to the root of your project
get_filename_component(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

# Use source_group with TREE to mirror directory structure
source_group(
    TREE "${ROOT_DIR}/include"
    PREFIX "Header Files"
    FILES ${HARVEST_HAVOC_HEADERS}
)
source_group(
    TREE "${ROOT_DIR}/src"
    PREFIX "Source Files"
    FILES ${HARVEST_HAVOC_SOURCES}
)

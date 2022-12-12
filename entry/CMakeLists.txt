# Path definitions.
set(entry_dir ${CMAKE_CURRENT_SOURCE_DIR})

# Add overall src library.
file(GLOB_RECURSE entry_main CONFIGURE_DEPENDS ${entry_dir}/*.cpp)
add_library(entry ${entry_main})
target_include_directories(entry PUBLIC ${entry_dir})

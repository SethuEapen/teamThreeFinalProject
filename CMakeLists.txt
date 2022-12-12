cmake_minimum_required(VERSION 3.0.0)
project(finalproject VERSION 0.1.0)

# include(CTest)
# enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Specify C++ compiler and linker.
if(NOT DEFINED EWS)
    set(CMAKE_C_COMPILER "/usr/bin/clang")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    set(CMAKE_LINKER "/usr/bin/clang++")
else()
    set(CMAKE_C_COMPILER "/software/llvm-6.0.1/bin/clang")
    set(CMAKE_CXX_COMPILER "/software/llvm-6.0.1/bin/clang++")
    set(CMAKE_LINKER "/software/llvm-6.0.1/bin/clang++")

    # Add other required flags for EWS.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif()

# Specify C++ Standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define project.   
project(${assignment_name} VERSION ${assignment_version})

# Specify Debug build.
set(CMAKE_BUILD_TYPE Debug)

# Specify warnings for all builds.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function")

# Specify debug symbols and no optimizations for Debug builds.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -O0 -gdwarf-4")

# Specify additional clean files.
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${assignment_clean_rm}")

# Add Catch2.
# Note: Ubuntu 20.04 LTS does not have Catch2 on apt
# See: https://github.com/catchorg/Catch2/issues/1383
if(NOT DEFINED EWS)
    find_package(Catch2 REQUIRED)
else()
    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.0-preview3
    )

    FetchContent_MakeAvailable(Catch2)

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

set(src_dir ${CMAKE_SOURCE_DIR}/src)
set(tests_dir ${CMAKE_SOURCE_DIR}/tests)
set(entry_dir ${CMAKE_SOURCE_DIR}/entry)

add_executable(finalproject main.cpp)

# Run CMakeLists in src_dir to build the student's code.
add_subdirectory(${src_dir})
# $(PROJECT_DIR)/../entry
add_subdirectory(${entry_dir})

# Add the Catch2 entrypoint using Catch2, our libs and src code.
file(GLOB_RECURSE tests_src CONFIGURE_DEPENDS ${tests_dir}/*.cpp)
# file(GLOB_RECURSE main_entry CONFIGURE_DEPENDS ${entry_dir}/*.cpp)
# file(GLOB_RECURSE source CONFIGURE_DEPENDS ${src_dir}/*.cpp)

# file(GLOB main ${entry_dir}/*.cpp)
# foreach(main ${entry_dir})
#     add_executable(main ${entry_dir})
# endforeach( main ${entry_dir} )

include(Catch)

add_executable(test ${tests_src})
# add_executable(main ${main_entry})
# add_executable(ss ${source})

target_link_libraries(test PRIVATE Catch2::Catch2WithMain entry src)

catch_discover_tests(test)

# Add the assignment entrypoints using our libs and src code.
foreach(entrypoint IN LISTS assignment_entrypoints)
    add_executable(${entrypoint} ${src_dir}/${entrypoint}.cpp)
    target_link_libraries(${entrypoint} PRIVATE src)
endforeach()
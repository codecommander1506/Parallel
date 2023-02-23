cmake_minimum_required(VERSION 3.20)

project(Parallel
    DESCRIPTION "Multithreading library"
    VERSION     1.0.0
    LANGUAGES   C CXX
)

# Test
option(Parallel_BUILD_TEST "Build Parallel test" OFF)

# Documentation
option(Parallel_BUILD_DOC "Build Parallel documentation" OFF)

# Translations
option(Parallel_BUILD_TRANSLATIONS "Build Parallel translations" OFF)

# Package
set(Parallel_COMPONENTS)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ParallelConfig.cmake.in ${CMAKE_BINARY_DIR}/lib/cmake/Parallel/ParallelConfig.cmake
    INSTALL_DESTINATION lib/cmake/Parallel
)

write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/lib/cmake/Parallel/ParallelConfigVersion.cmake
    VERSION       ${Parallel_VERSION}
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

# External packages
include(cmake/FindQt5.cmake)
include(cmake/FindCommander.cmake)

# Internal
include(cmake/ParallelHelpers.cmake)

# CXX Variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C Variables
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output locations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_subdirectory(src)

if (Parallel_BUILD_TEST)
    add_subdirectory(test)
endif()

if (Parallel_BUILD_DOC)
    add_subdirectory(doc)
endif()

# Packaging
parallel_export(${Parallel_COMPONENTS})


parallel_add_library(parallel)

set_target_properties(parallel
    PROPERTIES
        DISPLAY_NAME Parallel
        VERSION      ${Parallel_VERSION}
        SOVERSION    ${Parallel_VERSION}
        LOCALES      fr
)

target_include_directories(parallel
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(parallel PUBLIC Qt5::Core)

if (BUILD_SHARED_LIBS)
    set(BUILD_TYPE SHARED)
else()
    set(BUILD_TYPE STATIC)
endif()

target_compile_definitions(parallel
    PUBLIC  PARALLEL_${BUILD_TYPE} PARALLEL_LIB
    PRIVATE BUILD_PARALLEL_LIB
)

add_subdirectory(kernel)

if (Parallel_BUILD_TRANSLATIONS)
    include(translations.cmake)
endif()

parallel_install(TARGETS parallel EXPORT ParallelExport)


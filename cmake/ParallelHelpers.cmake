if (WIN32)
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

option(BUILD_SHARED_LIBS "Enable/disable shared build" ON)

function(parallel_add_executable name)
    commander_add_executable(${name} ${ARGN})
endfunction()

function(parallel_add_library name)
    commander_add_library(${name} ${ARGN})
endfunction()

macro(parallel_sources target)
    set_source_files_properties(${HEADERS2} PROPERTIES PRIVATE TRUE)

    target_files(${target} HEADERS ${HEADERS} ${HEADERS2} SOURCES ${SOURCES})

    unset(HEADERS)
    unset(HEADERS2)
    unset(SOURCES)
endmacro()

macro(parallel_install type)
    install(${type} ${ARGN})
endmacro()

macro(parallel_export)
    foreach (module "" ${ARGN})
        export(
            EXPORT    Parallel${module}Export
            NAMESPACE Parallel::
            FILE      ${CMAKE_BINARY_DIR}/lib/cmake/Parallel/Parallel${module}Targets.cmake
        )

        install(
            EXPORT      Parallel${module}Export
            NAMESPACE   Parallel::
            DESTINATION lib/cmake/Parallel
        )
    endforeach()
endmacro()

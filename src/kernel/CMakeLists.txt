configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)

set(HEADERS 
    config.h global.h
    debug.h
    thread.h job.h
)

set(HEADERS2
)

set(SOURCES
    debug.cpp
    thread.cpp job.cpp
)

parallel_sources(parallel)

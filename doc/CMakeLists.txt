configure_file(Doxyfile.in Doxyfile)

find_package(Doxygen REQUIRED)

find_program(qhelpgenerator qhelpgenerator REQUIRED)

add_custom_target(parallel_doc ALL
    Doxygen::doxygen  Doxyfile
    SOURCES           Doxyfile.in
)

add_dependencies(parallel_doc parallel)

install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/Parallel DESTINATION doc)

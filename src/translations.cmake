if (NOT EXISTS ${Parallel_SOURCE_DIR}/translations)
    file(MAKE_DIRECTORY ${Parallel_SOURCE_DIR}/translations)
endif()

get_target_property(TS_FILES parallel LOCALES)

list(TRANSFORM TS_FILES PREPEND ${Parallel_SOURCE_DIR}/translations/parallel_)
list(TRANSFORM TS_FILES APPEND  .ts)

qt5_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})

target_sources(parallel PRIVATE ${QM_FILES})

install(FILES ${QM_FILES} DESTINATION translations)

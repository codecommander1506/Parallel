enable_testing()

find_package(GTest REQUIRED)

add_executable(parallel_test main.cpp)

target_link_libraries(parallel_test GTest::gtest parallel)

add_subdirectory(kernel)

add_test(parallel COMMAND parallel_test)

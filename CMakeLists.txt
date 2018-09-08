cmake_minimum_required(VERSION 3.8)
project(cjr_lib)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(sandbox)

include(cmake/googletest.cmake)
fetch_googletest(
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_BINARY_DIR}/googletest
)

enable_testing()
add_subdirectory(test)

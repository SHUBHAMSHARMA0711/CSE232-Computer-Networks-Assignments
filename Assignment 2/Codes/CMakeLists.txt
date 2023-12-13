cmake_minimum_required(VERSION 3.27)
project(Assignment2)

# We will use C++ 17 for this Assignment 2
set(CMAKE_CXX_STANDARD 17)


include_directories("${PROJECT_SOURCE_DIR}/src/util/")
include_directories("${PROJECT_SOURCE_DIR}/src/")
include_directories("${PROJECT_SOURCE_DIR}/src/tcp_helpers/")

add_subdirectory(src)

enable_testing()

add_subdirectory(tests)
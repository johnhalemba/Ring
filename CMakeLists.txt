cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
project(lab1)
add_compile_options(-Wall -Wextra -pedantic -Werror)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(googletest)
add_executable(lab2 main.cpp Ring.h RingIterator.h)
add_executable(tests tests.cpp Ring.h RingIterator.h)

target_link_libraries(tests PUBLIC gtest_main)

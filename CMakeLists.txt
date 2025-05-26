cmake_minimum_required(VERSION 3.30.5)

project(dsa LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    -Wextra
    -Wno-c++17-extensions
)

include_directories(libs)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS tests/*.cpp)

add_executable(out ${SRC_FILES} ${TEST_FILES})

target_link_libraries(out PRIVATE gtest_main)

# Enable test discovery for CTest
enable_testing()
add_test(NAME RunAllTests COMMAND out --test)

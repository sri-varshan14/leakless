cmake_minimum_required(VERSION 3.28.0)

project(leakless)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g")

file(GLOB_RECURSE LEAKLESS_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(leakless STATIC ${LEAKLESS_SRC})
target_include_directories(leakless PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main bin/main.c)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main PUBLIC leakless)

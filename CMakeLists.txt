cmake_minimum_required(VERSION 3.15)
project(parc VERSION 0.0.1 LANGUAGES C)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(parc src/main.c)

include(CTest)

add_test(NAME TestCompilingAndRunning COMMAND parc port=123)
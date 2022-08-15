cmake_minimum_required(VERSION 3.15)
project(parc VERSION 0.0.1 LANGUAGES C)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(parc src/main.c)

target_link_libraries(parc PRIVATE m)

install(FILES "include/parc.h" DESTINATION include)

# Tests
add_executable(compile_test tests/compile_test.c)

add_executable(int_provided tests/int_provided.c)
add_executable(int_not_provided tests/int_not_provided.c)

add_executable(double_provided tests/double_provided.c)
add_executable(double_not_provided tests/double_not_provided.c)

add_executable(str_provided tests/str_provided.c)
add_executable(str_not_provided tests/str_not_provided.c)

add_executable(bool_provided tests/bool_provided.c)
add_executable(bool_not_provided tests/bool_not_provided.c)

include(CTest)

add_test(NAME TestCompilingAndRunning COMMAND compile_test)
add_test(NAME TestIntProvided COMMAND int_provided port=123)
add_test(NAME TestIntNotProvided COMMAND int_not_provided)
add_test(NAME TestDoubleProvided COMMAND double_provided val=2.71)
add_test(NAME TestDoubleNotProvided COMMAND double_not_provided)
add_test(NAME TestStrProvided COMMAND str_provided password=qwerty)
add_test(NAME TestStrNotProvided COMMAND str_not_provided)
add_test(NAME TestBoolProvided COMMAND bool_provided val)
add_test(NAME TestBoolNotProvided COMMAND bool_not_provided)
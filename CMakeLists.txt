cmake_minimum_required(VERSION 3.16)

project(roman)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_EXE rome.c)

set(SOURCE_LIB functions.c)

add_library(my_lib STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main my_lib)

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE "${GMOCK_INCLUDE_DIRS}" "${GTEST_INCLUDE_DIRS}")


set(TESTS_EXE tests.cpp )

add_executable(tests ${TESTS_EXE})


target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests my_lib)


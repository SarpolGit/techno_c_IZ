cmake_minimum_required(VERSION 3.16)

project(roman)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)


if (CMAKE_BUILD_TYPE MATCHES Debug)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  setup_target_for_coverage_gcovr_html(
    NAME coverage
    EXECUTABLE tests
    BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
    EXCLUDE "build/*" "tests/*" "rome.c")
endif()

set(SOURCE_EXE rome.c)

set(SOURCE_LIB functions.c)

add_library(my_lib STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main my_lib)

enable_testing()


find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})


add_executable(tests tests/tests.cpp tests/main.cpp)


target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests my_lib)


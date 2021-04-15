cmake_minimum_required(VERSION 3.1)
project(IZ2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)


if (CMAKE_BUILD_TYPE MATCHES Debug)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  setup_target_for_coverage_gcovr_html(
    NAME coverage
    EXECUTABLE tests
    BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
    EXCLUDE "build/*" "tests/*" "main.c" "lib/file")
endif()

add_library(consistently_realisation STATIC lib/consistently/counting_consistently.c)
target_include_directories(consistently_realisation PUBLIC lib/consistently)

add_library(parallel_realisation SHARED lib/parallel/counting_parallel.c)
target_include_directories(parallel_realisation PUBLIC lib/parallel)

add_library(files STATIC lib/file/file.c)
target_include_directories(files PUBLIC lib/file)

add_executable(main main.c)

target_link_libraries(main Threads::Threads)
target_link_libraries(main consistently_realisation)
target_link_libraries(main parallel_realisation)
target_link_libraries(main files)

enable_testing()
find_package(GTest REQUIRED)


include_directories(${GTEST_INCLUDE_DIRS})
message(${GTEST_LIBRARIES})

add_executable(tests tests/tests.cpp tests/main.cpp)

target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests consistently_realisation)
target_link_libraries(tests parallel_realisation)
target_link_libraries(tests files)



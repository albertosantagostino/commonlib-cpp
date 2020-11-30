project(commonlib)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

# Configure googletest
 configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
 execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                 WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
 execute_process(COMMAND ${CMAKE_COMMAND} --build .
                 WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
 add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                  ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                  EXCLUDE_FROM_ALL)

# Add test target
set(TEST_TARGET ${CMAKE_PROJECT_NAME}_tests)
file(GLOB TESTS ../test/*.cpp)
file(COPY ../test/data DESTINATION ${CMAKE_BINARY_DIR})
include(GoogleTest)
include_directories(../include/)
add_executable(${TEST_TARGET} ${TESTS})
target_link_libraries(${TEST_TARGET} gtest_main)
gtest_discover_tests(${TEST_TARGET} WORKING_DIRECTORY ../test TEST_PREFIX *_tests:)


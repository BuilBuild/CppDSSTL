cmake_minimum_required(VERSION 3.15)

project(gtest_gmock)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 查找 GTest
find_package(GTest REQUIRED)

message(STATUS "GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")
message(STATUS "GTEST_LIBRARIES: ${GTEST_LIBRARIES}")
message(STATUS "GTEST_MAIN_LIBRARIES: ${GTEST_MAIN_LIBRARIES}")

link_libraries(pthread)
link_libraries(GTest::gtest)
link_libraries(GTest::gmock)

include_directories(${GTEST_INCLUDE_DIRS})


add_subdirectory(GTest)
add_subdirectory(GMock)


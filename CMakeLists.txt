cmake_minimum_required(VERSION 3.15)
project(cpp_ds_stl)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/MyList)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/WritePool)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(test test.cpp)
add_executable(single_write_test SingleWritePoolTest.cpp)
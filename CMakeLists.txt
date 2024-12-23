cmake_minimum_required(VERSION 3.15)
project(cpp_ds_stl)

set(HEADER_DIRS ${PROJECT_SOURCE_DIR}/MyList)
list(APPEND HEADER_DIRS ${PROJECT_SOURCE_DIR}/WritePool ${PROJECT_SOURCE_DIR}/TimeS)

set(LIB_DIR_PATH ${PROJECT_SOURCE_DIR}/lib)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(base_SRCS ${PROJECT_SOURCE_DIR}/TimeS/TimeStamp.cpp)


include_directories(${HEADER_DIRS})

add_library(dss_base ${base_SRCS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(Test)
add_executable(test test.cpp)
add_executable(single_write_test SingleWritePoolTest.cpp)

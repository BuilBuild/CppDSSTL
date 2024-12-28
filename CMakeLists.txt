cmake_minimum_required(VERSION 3.15)
project(cpp_ds_stl)

# set(HEADER_DIRS ${PROJECT_SOURCE_DIR}/MyList)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -fPIC")
add_compile_definitions(LOGDEBUG=1)

set(HEADER_DIRS 
    ${PROJECT_SOURCE_DIR}/MyList
    ${PROJECT_SOURCE_DIR}/WritePool 
    # ${PROJECT_SOURCE_DIR}/TimeS
    # ${PROJECT_SOURCE_DIR}/Comm
    # ${PROJECT_SOURCE_DIR}/MyLog
    ${PROJECT_SOURCE_DIR}/MyMuduo
    )

include_directories(${HEADER_DIRS})

set(LIB_DIR_PATH ${PROJECT_SOURCE_DIR}/lib)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# set(base_SRCS 
# ${PROJECT_SOURCE_DIR}/TimeS/TimeStamp.cpp
# ${PROJECT_SOURCE_DIR}/MyLog/Logger.cpp
# )
# add_library(dss_base ${base_SRCS})

aux_source_directory( ${PROJECT_SOURCE_DIR}/MyMuduo muduo_SRC)
link_directories(${PROJECT_SOURCE_DIR}/lib)



add_library(muduo_base ${muduo_SRC})
# target_link_libraries(muduo_base dss_base)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(Test)
add_executable(test test.cpp)
add_executable(single_write_test SingleWritePoolTest.cpp)

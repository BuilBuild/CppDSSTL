
include_directories(${HEADER_DIRS})
link_directories(${LIB_DIR_PATH})
link_libraries(dss_base)
link_libraries(muduo_base)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(time_stamp_test time_stamp_test.cpp)
add_executable(logger_test logger_test.cpp)
add_executable(addr_test addr_test.cpp)
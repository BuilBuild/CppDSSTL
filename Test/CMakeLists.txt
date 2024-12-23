
include_directories(${HEADER_DIRS})
link_directories(${LIB_DIR_PATH})
link_libraries(dss_base)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(time_stamp_test time_stamp_test.cpp)
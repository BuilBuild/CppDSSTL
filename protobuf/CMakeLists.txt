
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/protobuf)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})  #添加头文件
include_directories(${CMAKE_CURRENT_BINARY_DIR})  #添加头文件
link_libraries(${PROTOBUF_LIBRARIES})


add_executable(addrbook_write addressbook_write.cpp addressbook.pb.cc )
add_executable(addrbook_read addressbook_read.cpp addressbook.pb.cc)
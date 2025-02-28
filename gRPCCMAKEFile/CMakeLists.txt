cmake_minimum_required(VERSION 3.15)
project(GenerateGRPCSources)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# 设置生成文件的输出目录
set(GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY   ${GENERATED_DIR})

# 定义你的 .proto 文件路径
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/OrderRequest.proto)

find_program(GRPC_CPP_PLUGIN_EXECUTABLE
    NAMES grpc_cpp_plugin
    PATHS "${gRPC_INSTALL_PREFIX}/bin" /usr/local/bin /usr/bin
    DOC "Path to gRPC C++ plugin"
)

if(NOT GRPC_CPP_PLUGIN_EXECUTABLE)
    message(FATAL_ERROR "grpc_cpp_plugin not found!")
else()
    message(STATUS "Found grpc_cpp_plugin: ${GRPC_CPP_PLUGIN_EXECUTABLE}")
endif()

find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)
if(NOT GRPC_CPP_PLUGIN)
    message(FATAL_ERROR "grpc_cpp_plugin not found!")
else()
    message(STATUS "Found grpc_cpp_plugin: ${GRPC_CPP_PLUGIN}")
endif()

add_custom_command(
    OUTPUT
        "${GENERATED_DIR}/OrderRequest.grpc.pb.cc"
        "${GENERATED_DIR}/OrderRequest.grpc.pb.h"
    COMMAND ${Protobuf_PROTOC_EXECUTABLE}
    ARGS
        --cpp_out=${GENERATED_DIR}
        --grpc_out=${GENERATED_DIR}
        --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
        -I=${PROTO_DIR}
        ${PROTO_FILE}
    DEPENDS  
        # ${PROTO_FILE}
        # ${PROTO_SRCS}
        # ${PROTO_HDRS}
    COMMENT "Generating gRPC code"
)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILE})

# 创建仅生成代码的目标
add_custom_target(generate_grpc_files
    DEPENDS
        "${GENERATED_DIR}/OrderRequest.grpc.pb.cc"
        "${GENERATED_DIR}/OrderRequest.grpc.pb.h"
    COMMENT "Triggering gRPC code generation"
)
add_library(order_request_lib STATIC
    ${PROTO_SRCS}
  "${GENERATED_DIR}/OrderRequest.grpc.pb.cc"
)

target_link_libraries(order_request_lib PUBLIC
  gRPC::grpc++
  gRPC::grpc
  protobuf::libprotobuf
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
link_directories()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(order_request_server server.cc)
# 链接库
target_link_libraries(order_request_server order_request_lib)

add_executable(order_request_client client.cc)
target_link_libraries(order_request_client order_request_lib)
# grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_FILE})
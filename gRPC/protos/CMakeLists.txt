set(PROTO_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
file(GLOB PROTO_FILE "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
message(${PROTO_OUT_DIR})

# 手动生成命令
add_custom_command(
  OUTPUT
    ${PROTO_OUT_DIR}/OrderRequest.pb.cc
    ${PROTO_OUT_DIR}/OrderRequest.pb.h
    ${PROTO_OUT_DIR}/OrderRequest.grpc.pb.cc
    ${PROTO_OUT_DIR}/OrderRequest.grpc.pb.h
  COMMAND
    protoc
    --grpc_out=${PROTO_OUT_DIR}
    --cpp_out=${PROTO_OUT_DIR}
    --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin
    --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
#   DEPENDS
#       \){PROTO_FILE}
)

add_library(grpc_proto STATIC
  "${PROTO_OUT_DIR}/OrderRequest.pb.cc"
  "${PROTO_OUT_DIR}/OrderRequest.grpc.pb.cc"
)
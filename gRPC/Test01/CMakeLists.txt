cmake_minimum_required(VERSION 3.10)
project(grpc_demo)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

add_executable(server server.cpp helloworld.grpc.pb.cc helloworld.pb.cc)
target_link_libraries(server PRIVATE gRPC::grpc++_reflection gRPC::grpc++ protobuf::libprotobuf)


add_executable(client client.cpp helloworld.grpc.pb.cc helloworld.pb.cc)
target_link_libraries(client PRIVATE gRPC::grpc++_reflection gRPC::grpc++ protobuf::libprotobuf)
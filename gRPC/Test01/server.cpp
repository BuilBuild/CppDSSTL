/*
 * @Author: LeiJiulong
 * @Date: 2025-02-23 19:41:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-23 20:59:20
 * @Description: 
 */
#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"

class GreeterServiceImpl final : public helloworld::Greeter::Service {
  grpc::Status SayHello(::grpc::ServerContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloResponse* response) override {
    response->set_message("hello world!");
    return grpc::Status::OK;
  }
};

int main() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
  GreeterServiceImpl service;
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
  return 0;
}
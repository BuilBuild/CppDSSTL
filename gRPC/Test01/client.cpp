/*
 * @Author: LeiJiulong
 * @Date: 2025-02-23 19:43:09
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-23 20:49:57
 * @Description: 
 */
#include <grpcpp/grpcpp.h>
#include <memory>
#include "helloworld.grpc.pb.h"

using namespace helloworld;

int main() {
  auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
  auto stub = Greeter::NewStub(channel);
  HelloRequest request;
  request.set_name("World");
  HelloResponse response;
  grpc::ClientContext context;
  grpc::Status status = stub->SayHello(&context, request, &response);
  

  if (status.ok()) {
    std::cout << "Response: " << response.message() << std::endl;
  } else {
    std::cout << "RPC failed: " << status.error_message() << std::endl;
  }
  return 0;
}
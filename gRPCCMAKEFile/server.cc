/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 21:12:05
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 21:41:32
 * @Description: 
 */

#include "generated/OrderRequest.grpc.pb.h"

#include <grpcpp/grpcpp.h>
#include <string>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;


 class OrderServiceImpl final : public  OrderService::Service{
     grpc::Status CreateOrder(ServerContext* context, const OrderRequest* request, OrderResponse* response) override{
        response->set_order_id("12345");
        response->set_customer_id("5566");
        return Status::OK;
     }
 };


 int main(int argc, char** argv)
 {
    std::string serverAddress("0.0.0.0:50051");
    ServerBuilder builder;
    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());

    OrderServiceImpl service;
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << serverAddress << std::endl;
    server->Wait();
    return 0;
     
 }
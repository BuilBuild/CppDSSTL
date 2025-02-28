/*
 * @Author: LeiJiulong
 * @Date: 2025-02-28 21:53:01
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-28 22:04:52
 * @Description: 
 */

#include "generated/OrderRequest.grpc.pb.h"

#include <grpcpp/grpcpp.h>
#include <memory>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class OrderServiceClient 
{
public:
    OrderServiceClient(std::shared_ptr<Channel> channel): stub_(OrderService::NewStub(channel)) {}

    std::string CreateOrder(const std::string& order_name)
    {
        OrderRequest request;
        request.set_order_id(order_name);
        OrderResponse response;
        ClientContext context;
        Status status = stub_->CreateOrder(&context, request, &response);
        if (status.ok()) 
        {
            return response.order_id();
        }
        else
        {
            return "RPC failed";
        }
    }
private:
    std::unique_ptr<OrderService::Stub> stub_;
};

int main(int argc, char* argv[]) 
{
    OrderServiceClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::string order_id = client.CreateOrder("order1");

    std::cout << "Received Order ID: " << order_id << std::endl;
    return 0;
}

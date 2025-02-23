###
 # @Author: LeiJiulong
 # @Date: 2025-02-23 19:41:03
 # @LastEditors: LeiJiulong && lei15557570906@outlook.com
 # @LastEditTime: 2025-02-23 19:41:05
 # @Description: 
### 
protoc -I=. --grpc_out=. --cpp_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` helloworld.proto
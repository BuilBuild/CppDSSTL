# protoc -I=. route_guide.proto --cpp_out=.
# protoc -I=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` route_guide.proto

cmake_minimum_required(VERSION 3.15)
project(GrpcTest)

set(CMAKE_CXX_STANDARD_REQUIRED 17)



include_directories(${CMAKE_CURRENT_BINARY_DIR}/protos)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory(protos)
add_subdirectory(Test02)





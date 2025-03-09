cmake_minimum_required(VERSION 3.15)
project(web_socket)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_libraries(${Boost_LIBRARIES})

add_subdirectory(src)


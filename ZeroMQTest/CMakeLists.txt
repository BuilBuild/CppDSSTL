

link_libraries(zmq)

add_executable(taskvent taskvent.c)
add_executable(taskwork taskwork.c)
add_executable(tasksink tasksink.c)
add_executable(PUB_test PUB_test.cpp)
add_executable(SUB_test SUB_test.cpp)
# target_link_libraries(taskvent zmq)
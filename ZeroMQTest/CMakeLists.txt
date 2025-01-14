
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/ZeroMQTTest)

link_libraries(zmq)

add_executable(taskvent taskvent.c)
add_executable(taskwork taskwork.c)
add_executable(tasksink tasksink.c)
add_executable(PUB_test PUB_test.cpp)
add_executable(SUB_test SUB_test.cpp)
add_executable(REQ_test REQ_test.cpp)
add_executable(REP_test REP_test.cpp)
add_executable(XSPubHub XSPubHub.cpp)
add_executable(HubPub01 HubPub01.cpp)
add_executable(HubPub02 HubPub02.cpp)
add_executable(HubSub01 HubSub01.cpp)


# target_link_libraries(taskvent zmq)
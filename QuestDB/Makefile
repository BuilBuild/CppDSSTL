# g++ ClientTest.cpp -lquestdb_client

CXX = g++
CXX_FLAG=-std=c++17 
LIBS=-lquestdb_client

.PHONY : all
all: clientTest

clientTest :
	$(CXX) $(CXX_FLAG) -o clientTest ClientTest.cpp $(LIBS)
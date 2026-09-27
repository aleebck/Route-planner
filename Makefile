CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Ithird_party

routeplanner: src/main.cpp src/Graph.cpp include/Graph.h
	$(CXX) $(CXXFLAGS) src/main.cpp src/Graph.cpp -o routeplanner

server: src/server.cpp src/Graph.cpp include/Graph.h
	$(CXX) $(CXXFLAGS) src/server.cpp src/Graph.cpp -o server
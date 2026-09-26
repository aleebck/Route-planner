CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

routeplanner: src/main.cpp src/Graph.cpp include/Graph.h
	$(CXX) $(CXXFLAGS) src/main.cpp src/Graph.cpp -o routeplanner
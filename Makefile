CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

routeplanner:
	$(CXX) $(CXXFLAGS) src/main.cpp src/Graph.cpp -o routeplanner
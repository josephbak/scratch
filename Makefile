CXX = /usr/bin/clang++
CXXFLAGS = -std=c++17

main: main.cpp bump_allocator.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o main
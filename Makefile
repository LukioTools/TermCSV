

all:
	c++ -std=c++20 -o testt3 testv3.cpp $(find v3/src -name "*.cpp")

link:
	c++ -std=c++20 -o testt3 testv3.cpp $(find v3/bin -name "*.o")
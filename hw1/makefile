CXX = g++
CXXFLAGS = -Wall -g

hw1: main.o auxArrayFunctions.o sorting.o
	$(CXX) $(CXXFLAGS) -o hw1 main.o auxArrayFunctions.o sorting.o

main.o: main.cpp auxArrayFunctions.h sorting.h
	$(CXX) $(CXXFLAGS) -c main.cpp
auxArrayFunctions.o: auxArrayFunctions.h
hw1part2.o: sorting.h

clean:
	rm hw1 *.o

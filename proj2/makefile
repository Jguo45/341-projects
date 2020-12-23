CXX = g++
CXXFLAGS = -Wall

driver: driver.cpp bookTree.o bNode.o wordTree.o
	$(CXX) $(CXXFLAGS) driver.cpp bookTree.o bNode.o wordTree.o -o driver

mytest: mytest.cpp bookTree.o bNode.o wordTree.o
	$(CXX) $(CXXFLAGS) mytest.cpp bookTree.o bNode.o wordTree.o -o mytest

wordTree.o: wordTree.h wordTree.cpp
	$(CXX) $(CXXFLAGS) -c wordTree.cpp

bNode.o: bNode.h bNode.cpp
	$(CXX) $(CXXFLAGS) -c bNode.cpp

bookTree.o: bookTree.h bookTree.cpp
	$(CXX) $(CXXFLAGS) -c bookTree.cpp

clean:
	rm *.o
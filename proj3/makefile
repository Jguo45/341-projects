CXX = g++
CXXFLAGS = -Wall

mytest: mytest.cpp pqueue.cpp
	$(CXX) $(CXXFLAGS) mytest.cpp pqueue.cpp -o mytest

driver: driver.cpp pqueue.cpp
	$(CXX) $(CXXFLAGS) driver.cpp pqueue.cpp -o driver

clean:
	rm *.o
CXX = g++
CXXFLAGS = -Wall

driver: driver.cpp csrlist.o csr.o
	$(CXX) $(CXXFLAGS) driver.cpp csrlist.o csr.o -o driver

mytest: mytest.cpp csrlist.o csr.o
	$(CXX) $(CXXFLAGS) mytest.cpp csrlist.o csr.o -o mytest

test: test.cpp csr.cpp
	$(CXX) $(CXXFLAGS) test.cpp csr.cpp -o test

csrlist.o: csrlist.h csrlist.cpp csr.o
	$(CXX) $(CXXFLAGS) -c csrlist.cpp

csr.o: csr.h csr.cpp
	$(CXX) $(CXXFLAGS) -c csr.cpp
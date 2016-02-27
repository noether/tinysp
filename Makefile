CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++11
LIBS = -lbluetooth

OBJECTS_TEST = serialport.o tinysp.o test_comm.o

all: test_comm

test_comm: $(OBJECTS_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) *~ *.o test_comm

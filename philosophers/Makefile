CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -pthread

TARGET = dining_philosophers
SRC = dining_philosophers.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
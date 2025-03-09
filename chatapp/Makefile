CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -pthread

TARGETS = chat_client chat_server
SRC_CLIENT = chat_client.cpp
SRC_SERVER = chat_server.cpp

all: $(TARGETS)

chat_client: $(SRC_CLIENT)
	$(CXX) $(CXXFLAGS) -o $@ $^

chat_server: $(SRC_SERVER)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)

.PHONY: all clean
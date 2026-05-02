CXX ?= g++

SRC := $(wildcard src/*.cc src/*.cpp)
OBJ := $(SRC:.cc=.o) $(SRC:.cpp=.o)
OUT := nclock

LDFLAGS := -lncurses -lform -std=c++20
CXXFLAGS := -std=c++20 -O2 -Iinclude

$(OUT): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean: 
	rm -f $(OUT) $(OBJ)

run: $(OUT)
	./$(OUT)

.PHONY: clean run
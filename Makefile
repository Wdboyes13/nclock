CXX ?= g++

SRC := $(wildcard src/*.cc)
OBJ := $(SRC:.cc=.o)
OUT := nclock

LDFLAGS := -lncurses -lform -std=c++20
CXXFLAGS := -std=c++20 -O2 -Iinclude

$(OUT): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^
%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean: 
	rm -f $(OUT) $(OBJ)

run: $(OUT)
	./$(OUT)

.PHONY: clean run
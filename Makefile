CXX ?= g++
STRIP ?= strip

SRC := $(wildcard src/*.cc)
OBJ := $(SRC:.cc=.o)
OUT := nclock

OS := $(shell uname -o)

ifeq ($(OS),Darwin)
GCFLAG := -Wl,-dead_strip
else
GCFLAG := -Wl,--gc-sections
endif

LDFLAGS := -lncurses -lform -std=c++20 $(GCFLAG)
CXXFLAGS := -std=c++20 -O2 -isystem include -Wall -Wextra -Werror -ffunction-sections -fdata-sections

$(OUT): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^
ifneq ($(NOSTRIP),1)
	$(STRIP) $@
endif

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean: 
	rm -f $(OUT) $(OBJ)

run: $(OUT)
	./$(OUT)

.PHONY: clean run
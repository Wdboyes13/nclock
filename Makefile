CXX ?= g++

SRC := $(wildcard src/*.cc)
OBJ := $(SRC:.cc=.o)
OUT := nclock

LDFLAGS := -lncurses -lform
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra -Iinclude

$(OUT): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean: 
	rm -f $(OUT) $(OBJ)

run: $(OUT)
	./$(OUT)

install: $(OUT)
	install -Dm755 $(OUT) $(DESTDIR)/usr/local/bin/$(OUT)
	install -Dm644 standard.flf $(DESTDIR)/usr/local/share/nclock/standard.flf

.PHONY: clean run install
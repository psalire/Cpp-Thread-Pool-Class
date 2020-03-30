
BIN = bin
EXECS = main_test
CC = g++ -std=c++17 -O3 -Iinclude -Isrc
FLAGS = -Wall -Wextra -Wpedantic
LINKS = -pthread
SRC = $(wildcard src/*.cc)

.PHONY: all, clean, test, remake

all: $(EXECS)

### Executables ###
main_test: src/main_test.cc
	$(CC) -o $@ $< $(FLAGS) $(LINKS)

### Clean ###
clean:
	rm -f $(EXECS) $(wildcard bin/*.o)

# Make and run
test:
	make && ./main_test
    
# Clean and make
remake:
	make clean && make

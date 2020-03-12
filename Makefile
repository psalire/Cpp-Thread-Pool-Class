
BIN = bin
EXECS = main_test
CC = g++ -std=c++17 -Iinclude -Isrc
FLAGS = -Wall -Wextra -Wpedantic
LINKS = -pthread
OBJECTS = $(BIN)/thread_pool.o
SRC = $(wildcard src/*.cc)

.PHONY: all, clean, test, remake

all: $(EXECS)

### Executables ###
main_test: src/main_test.cc
	$(CC) -o $@ $< $(FLAGS) $(LINKS)

### Objects ###
bin/%.o: src/%.cc
	$(CC) -c $< $(LINKS) $(FLAGS)
	@mv *.o $(BIN)

### Clean ###
clean:
	rm -f $(EXECS) $(wildcard bin/*.o)

# Make and run
test:
	make && ./main_test
    
# Clean and make
remake:
	make clean && make

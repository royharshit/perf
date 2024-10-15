# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Define the source and target
SRC = hw_cycles.c
TARGET = hw_cycles

# Default target to build and run the program
.PHONY: all
all: $(TARGET) run

# Rule to compile the source file
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Rule to run the executable
.PHONY: run
run:
	sudo ./$(TARGET)

# Rule to clean up the build files
.PHONY: clean
clean:
	rm -f $(TARGET)


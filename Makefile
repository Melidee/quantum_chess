# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I./raylib-5.5_linux_amd64/include

# Linker flags
LDFLAGS = -L./raylib-5.5_linux_amd64/lib -lraylib -lm -lpthread -ldl -lrt -lX11

# Source files
SRC = src/main.c

# Output executable
OUTPUT = main

# Default target
all: $(OUTPUT)

# Build the executable
$(OUTPUT): $(SRC)
	$(CC) $(SRC) -o $(OUTPUT) $(CFLAGS) $(LDFLAGS)

# Phony target for build
.PHONY: build
build:
	$(CC) $(SRC) -o $(OUTPUT) $(CFLAGS) $(LDFLAGS)

# Run target
.PHONY: run
run: $(OUTPUT)
	LD_LIBRARY_PATH=./raylib-5.5_linux_amd64/lib:$$LD_LIBRARY_PATH ./$(OUTPUT)

# Clean target
.PHONY: clean
clean:
	rm -f $(OUTPUT)

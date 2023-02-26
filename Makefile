SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INC_DIR := include
LIB_DIR := lib

# Compiler
CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99 -g -I$(INC_DIR)

# Linker
LD := gcc
LDFLAGS := -L$(LIB_DIR)

# Libraries
LIBS := -lm

# Files

# Source files
SRC := $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Executable
BIN := $(BIN_DIR)/main

# Rules
.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Test against memory leaks with valgrind
.PHONY: test

test: $(BIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $(BIN)
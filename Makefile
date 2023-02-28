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

# Static analysis
CPPCHECKFLAGS := --enable=all --inconclusive --std=c99 --language=c \
				--check-library --suppress=missingIncludeSystem \
				--suppress=unusedFunction

# Memory leak detection
VALGRINGFLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

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
.PHONY: all clean debug test docs check

# Compile without debug flags
all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile with debug flags
debug: CFLAGS += -DDEBUG -g
debug: all

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Test against memory leaks with valgrind
test: $(BIN)
	valgrind $(VALGRINGFLAGS) $(BIN)

# run doxygen to generate documentation
docs:
	doxygen doxygen.cfg

# run cppcheck to check for errors
check:
	cppcheck $(CPPCHECKFLAGS) $(SRC_DIR) $(INC_DIR)
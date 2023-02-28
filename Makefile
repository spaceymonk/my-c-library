# ============================================================================ #
#                                    FOLDERS                                   #
# ============================================================================ #

SRC_DIR := src
TEST_DIR := test
INC_DIR := include
LIB_DIR := lib
OUT_DIR := out
BIN_DIR := $(OUT_DIR)/bin
OBJ_DIR := $(OUT_DIR)/obj

# ============================================================================ #
#                                     FILES                                    #
# ============================================================================ #

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRC))
TEST_BIN := $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_SRC))

# ============================================================================ #
#                                     FLAGS                                    #
# ============================================================================ #

# ------------------------------ Compiler Flags ------------------------------ #
CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99 -g -I$(INC_DIR)

# ------------------------------- Linker Flags ------------------------------- #
LD := gcc
LDFLAGS := -L$(LIB_DIR)

# ------------------------------ Static Analysis ----------------------------- #
CPPCHECKFLAGS := --enable=all --inconclusive --std=c99 --language=c \
				--check-library --suppress=missingIncludeSystem \
				--suppress=unusedFunction -I $(INC_DIR)

# --------------------------- Memory Leak Detection -------------------------- #
VALGRINGFLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes \
				--verbose

# ------------------------------- Library Flags ------------------------------ #
LIBS := -lm

# ============================================================================ #
#                                     RULES                                    #
# ============================================================================ #
.PHONY: all clean debug memcheck docs check

all: $(TEST_BIN)

$(TEST_BIN): $(OBJ) $(TEST_OBJ) | $(BIN_DIR)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

debug: CFLAGS += -DDEBUG -g
debug: all

clean:
	rm -rf $(OUT_DIR)

memcheck: $(TEST_BIN)
	valgrind $(VALGRINGFLAGS) $(TEST_BIN)

docs:
	doxygen doxygen.cfg

check:
	cppcheck $(CPPCHECKFLAGS) $(SRC_DIR) $(TEST_DIR)
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
				--error-exitcode=1 --quiet

# ------------------------------- Library Flags ------------------------------ #
LIBS := -lm

# ============================================================================ #
#                                     RULES                                    #
# ============================================================================ #
.PHONY: all clean debug memcheck docs cppcheck

all: $(TEST_BIN)

$(TEST_BIN): $(OBJ) $(TEST_OBJ) | $(BIN_DIR)
# we need to link the test files one by one because they are separate exes
# i am using eval to shorten the next line
	$(eval ld := $(LD) $(LDFLAGS) $(OBJ) $(LIBS))
# then for each test file we link it with the object files and the libraries
	$(foreach test, $(TEST_BIN), \
		$(ld) $(patsubst $(BIN_DIR)/%, $(OBJ_DIR)/%.o, $(test)) -o $(test);)
# below is the same as above but from obj to bin which requires more work
#	$(foreach test, $(TEST_OBJ), $(LD) $(LDFLAGS) $(OBJ) $(test) -o $(BIN_DIR)/$(notdir $(basename $(test))) $(LIBS);)
# below links all test files into one executable which is not what we want
#	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)


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
	rm -f vgcore.*

memcheck: $(TEST_BIN)
# run each test file through valgrind and check for memory leaks
# if there are any leaks valgrind will return a non-zero exit code
# which will cause the makefile to exit with an error
	$(foreach test, $(TEST_BIN), \
		echo $(test);  valgrind $(VALGRINGFLAGS) $(test);)

docs:
	doxygen doxygen.cfg

cppcheck:
	cppcheck $(CPPCHECKFLAGS) $(SRC_DIR) $(TEST_DIR)
# Compiler and flags
CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -std=c11 -pedantic -Iinclude
LDFLAGS  := -Llib
LDLIBS   := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Directories
APP_DIR    := app
ENGINE_DIR := engine
GAME_DIR   := game
UTILS_DIR  := utils
TEST_DIR   := test
BUILD_DIR  := build
OBJ_DIR    := $(BUILD_DIR)/obj
BIN_DIR    := $(BUILD_DIR)/bin

# Target executable
TARGET := $(BIN_DIR)/game

# Source files
SRC := \
	main.c \
	$(wildcard $(APP_DIR)/*.c) \
	$(wildcard $(ENGINE_DIR)/*.c) \
	$(wildcard $(GAME_DIR)/*.c) \
	$(wildcard $(UTILS_DIR)/*.c)

# Object files
OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# Test files
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SRC))
TEST_BIN := $(BIN_DIR)/tests

# Default target
all: build

# Build project
build: $(TARGET)

# Link executable
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

# Compile source files separately
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build test executable
test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) $(filter-out $(OBJ_DIR)/main.o,$(OBJ))
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

play: 
	./build/bin/game

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Rebuild everything
rebuild: clean build

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: rebuild

# Phony targets
.PHONY: all build clean rebuild debug test

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinc

# Directories
SRC_DIR := src
INC_DIR := inc
BIN_DIR := bin
OBJ_DIR := obj

# Find all .cpp files recursively in SRC_DIR
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Convert source files to object files in OBJ_DIR
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Output binary name
TARGET := $(BIN_DIR)/nse_client

# Default rule
all: $(TARGET)

# Link object files to create final binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild


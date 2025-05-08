# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinc -Iutil

# Directories
SRC_DIR := src
UTIL_DIR := util
INC_DIR := inc
OBJ_DIR := obj
BIN_DIR := bin

# Common utility source files (no main)
UTIL_SRCS := $(wildcard $(UTIL_DIR)/*.cpp) $(wildcard $(SRC_DIR)/mdp.cpp)
UTIL_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(UTIL_SRCS)))

# All main programs
MAIN_SRCS := $(wildcard $(SRC_DIR)/main_*.cpp)
EXEC_NAMES := $(patsubst $(SRC_DIR)/main_%.cpp,$(BIN_DIR)/%,$(MAIN_SRCS))

# Default target
all: prep $(EXEC_NAMES)

# Create needed dirs
prep:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Rule to build each executable
$(BIN_DIR)/%: $(SRC_DIR)/main_%.cpp $(UTIL_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Built $@"

# Compile utility and mdp sources to obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTIL_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned all build files."

# Run all executables
run: all
	@for exe in $(EXEC_NAMES); do echo "Running $$exe"; ./$$exe; done

.PHONY: all clean prep run


# Define the compiler and flags
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++17

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Find all source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Target executable name
TARGET = $(BIN_DIR)/main

# Default rule to build the executable
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)              # This is an explicit rule
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile .cpp files into .o files (implicit pattern rule)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the program after building it
run: $(TARGET)
	@./$(TARGET)

# Clean up the build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean run

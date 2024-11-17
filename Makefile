# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXEC = $(BIN_DIR)/main

# Default target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(EXEC)

# Compiling source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/main

# Run the executable
run: $(EXEC)
	./$(EXEC)

# Rebuild the project
rebuild: clean all

.PHONY: all clean run rebuild


# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17

# Project details
TARGET = bipartite_matching
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
LIBRARY = libbipartite_matching.a

# Source files and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Default target
all: setup $(BIN_DIR)/$(TARGET)

# Create directories if they don't exist
setup:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Compile each source file into the build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Archive object files into a library
$(LIBRARY): $(OBJ_FILES)
	@ar rcs $@ $^

# Link the executable from object files
$(BIN_DIR)/$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(BIN_DIR)/$(TARGET)
	@echo "Running the program..."
	./$(BIN_DIR)/$(TARGET) input.txt output.txt

testing: $(BIN_DIR)/$(TARGET)
	@echo "Running the program..."
	./$(BIN_DIR)/$(TARGET) large_input.txt output.txt

# Clean target to remove build artifacts
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR) $(LIBRARY)
	@echo "Cleaned build files."

# Install target
install: all
	@echo "Installing $(TARGET)..."
	@cp $(BIN_DIR)/$(TARGET) /usr/local/bin/
	@echo "Installed to /usr/local/bin/$(TARGET)."

# Uninstall target
uninstall:
	@echo "Uninstalling $(TARGET)..."
	@rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstalled $(TARGET)."

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build the project."
	@echo "  clean     - Remove all build artifacts."
	@echo "  install   - Install the program to /usr/local/bin."
	@echo "  uninstall - Uninstall the program from /usr/local/bin."
	@echo "  help      - Show this help message."

.PHONY: help build test clean install run

# Compiler
CXX = g++
CXXFLAGS = -Wall -g

# Files
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = tagFinder

help:
	@echo "Available targets:"
	@echo "  build    - Build the project"
	@echo "  test     - Run tests"
	@echo "  clean    - Remove build artifacts"
	@echo "  install  - Install dependencies"
	@echo "  run      - Run the project"

# Default build
build: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(TARGET)

# Test
test:
	@echo "Running tests..."

# Install
install:
	@echo "Installing dependencies..."

# Run
run: build
	./$(TARGET)
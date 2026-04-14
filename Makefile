.PHONY: help build test clean install run

help:
	@echo "Available targets:"
	@echo "  build    - Build the project"
	@echo "  test     - Run tests"
	@echo "  clean    - Remove build artifacts"
	@echo "  install  - Install dependencies"
	@echo "  run      - Run the project"

build:
	@echo "Building..."

test:
	@echo "Running tests..."

clean:
	@echo "Cleaning..."

install:
	@echo "Installing dependencies..."

run: build
	@echo "Running project..."
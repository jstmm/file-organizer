# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -g

# Directories
SRC_DIR = .
BUILD_DIR = build

# Source files
SRC_FILES = $(SRC_DIR)/main.cpp

# Output binary
TARGET = $(BUILD_DIR)/file_organizer

# Default target to build the project
all: $(TARGET)

# Rule to create the build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Rule to compile and link directly to the target binary, no object files
$(TARGET): $(SRC_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_FILES)

# Rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)
	mkdir -p test_directory
	rm -rf test_directory/**
	touch test_directory/image.jpg
	touch test_directory/document.txt
	touch test_directory/video.mp4
	touch test_directory/music.mp3
	touch test_directory/archive.zip

# Phony targets (not actual files)
.PHONY: all clean

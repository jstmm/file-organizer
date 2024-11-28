# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -g

# Target executable
TARGET = file_organizer

# Source files
SRCS = main.cpp

# Default target
all: $(TARGET)

# Compile source files directly into the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean up the executable
clean:
	rm -f $(TARGET)
	mkdir -p test_directory
	rm -rf test_directory/**
	touch test_directory/image.jpg
	touch test_directory/document.txt
	touch test_directory/video.mp4
	touch test_directory/music.mp3
	touch test_directory/archive.zip

# Phony targets
.PHONY: all clean

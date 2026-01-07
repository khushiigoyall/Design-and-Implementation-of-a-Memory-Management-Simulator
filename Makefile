# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Source files
SRC = src/main.cpp \
      src/allocator.cpp \
      src/buddy.cpp \
      src/cache.cpp \
      src/virtual_memory.cpp

# Output executable
TARGET = memory_simulator

# Default rule
all: $(TARGET)

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)

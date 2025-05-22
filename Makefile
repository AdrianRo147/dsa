# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Ilibs

# Find all .cpp files in src and subfolders
SRC = $(shell find src -name "*.cpp")

# Replace .cpp with .o for object files
OBJ = $(SRC:.cpp=.o)

# Output binary name
TARGET = out

# Build all
all: $(TARGET)

# Link object files into the target binary
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp into a .o
# Handle object files in subfolders safely
%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(TARGET)
	find src -name "*.o" -delete

.PHONY: all clean


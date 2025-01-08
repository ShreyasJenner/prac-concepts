# Compiler and flags
CXX=g++
CXXFLAGS=-Wall -Wextra -Iinclude -Iextern
LDFLAGS=-lftxui-component -lftxui-dom -lftxui-screen \
			-Lftxui/_deps/ftxui-build

# Project Structure
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
TARGET=$(BIN_DIR)/screen

# Find all .cpp files in SRC_DIR recursively
SRCS=$(shell find $(SRC_DIR) -name '*.cpp')
OBJS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Build the target
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build objects and executables
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean


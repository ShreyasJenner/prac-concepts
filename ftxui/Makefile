# compiler and flags
CXX=g++
CXXFLAGS=-Wall -Wextra -Iinclude -Iextern
LDFLAGS=-lftxui-component -lftxui-dom -lftxui-screen \
				-Lftxui/_deps/ftxui-build \

# Project Structure
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
DEMOTARGET=$(BIN_DIR)/demo

# find all .cpp files in SRC_DIR recursively and compile 
# corresponding object files in OBJ_DIR
SRCS=$(shell find $(SRC_DIR) -name '*.cpp')
OBJS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))


# demo target
demo:  $(DEMOTARGET)

# rule to build final executable
$(DEMOTARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX)  -o $@ $^ $(STATICLD) $(LDFLAGS)


# rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX)  -c $< -o $@


# clean build objects
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony target
.PHONY: demo clean


WORK_DIR = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build

$(shell mkdir -p $(BUILD_DIR))

INC_PATH = $(realpath include)
INC_FLAG = $(addprefix -I, $(INC_PATH))

COMMON_FLAGS = -O2 -Wall -Wextra $(INC_FLAG)

CC = gcc
CXX = g++
AS = as
LD = ld

CFLAGS = $(COMMON_FLAGS)
CXXFLAGS = $(COMMON_FLAGS)

SRCS = $(shell find source -name *.cpp) $(shell find source -name *.c)
OBJS = $(subst source/, $(BUILD_DIR)/source/, $(addsuffix .o, $(basename $(SRCS))))

compile: $(BUILD_DIR)/game
	@echo Compilation finished!

run: compile
	@$(BUILD_DIR)/game

$(BUILD_DIR)/game: $(OBJS)
	@$(CXX) -o $@ $(OBJS)

$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(dir $@) && echo + $(CXX) $<
	@$(CXX) -std=c++14 -c -o $@ $(CXXFLAGS) $(realpath $<)

$(BUILD_DIR)/%.o : %.c
	@mkdir -p $(dir $@) && echo + $(CC) $<
	@$(CC) -std=gnu11 -c -o $@ $(CFLAGS) $(realpath $<)

clean:
	-@rm -rf build

.PHONY: clean compile

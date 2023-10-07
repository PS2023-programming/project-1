WORK_DIR = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build

$(shell mkdir -p $(BUILD_DIR))

INC_PATH = $(realpath minitui/include) $(realpath game/include)
INC_FLAG = $(addprefix -I, $(INC_PATH))

COMMON_FLAGS = -O2 -MMD -Wall -Wextra $(INC_FLAG)
CFLAGS = $(COMMON_FLAGS)
CXXFLAGS = $(COMMON_FLAGS)

CC = gcc
CXX = g++
AS = as
LD = ld

SRCS = $(shell find minitui/source -name *.cpp) $(shell find minitui/source -name *.c) $(shell find game/source -name *.c) $(shell find game/source -name *.cpp)
OBJS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SRCS))))

compile: $(BUILD_DIR)/game
	@echo Compilation finished!

run: compile
	@$(BUILD_DIR)/game 2>$(BUILD_DIR)/game.log

$(BUILD_DIR)/shell:  wrapper/shell.c
	@gcc -Iinclude -o $(BUILD_DIR)/shell wrapper/shell.c

shell: $(BUILD_DIR)/shell
	@$(BUILD_DIR)/shell

$(BUILD_DIR)/game: $(OBJS)
	@$(CXX) -o $@ $(OBJS)

$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(dir $@) && echo + $(CXX) $<
	@$(CXX) -std=c++14 -c -o $@ $(CXXFLAGS) $(realpath $<)
	@sed -i 's/C:\/msys64//g' $(patsubst %.o, %.d, $@)

$(BUILD_DIR)/%.o : %.c
	@mkdir -p $(dir $@) && echo + $(CC) $<
	@$(CC) -std=gnu11 -c -o $@ $(CFLAGS) $(realpath $<)
	@sed -i 's/C:\/msys64//g' $(patsubst %.o, %.d, $@)

-include $(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(basename $(SRCS))))

clean:
	-@rm -rf build

.PHONY: clean compile run

CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra
LDFLAGS :=

SRC_DIR := src
BUILD_DIR := build
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))
DEP := $(OBJ:.o=.d)

TARGET := $(BUILD_DIR)/guessNumber

BUILD_TYPE ?= debug
ifeq ($(BUILD_TYPE), release)
	CXXFLAGS += -O2
else
	CXXFLAGS += -g -O0
endif

CXXFLAGS += -I include

.PHONY : default
default : all

.PHONY : all
all : $(TARGET)

$(TARGET) : $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "\033[0;32mBuild complete!\033[0m"

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -MMD -MP $< -o $@

-include $(DEP)

.PHONY : clean
clean :
	rm -rf $(BUILD_DIR)/*
	@echo "Cleaned build artifacts"

.PHONY : run
run : $(TARGET)
	@./$(TARGET) 2>/dev/null

.PHONY : debug
debug : $(TARGET)
	@./$(TARGET)

.PHONY: help
help:
	@echo "Usage:"
	@echo "  make                     Build the project (debug mode)"
	@echo "  make BUILD_TYPE=release  Build optimized"
	@echo "  make run                 Build and run"
	@echo "  make clean               Remove build artifacts"
	@echo "  make help                Show this help"
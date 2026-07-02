CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra
LDFLAGS :=

SRC_DIR := src
SCRIPTS_DIR := scripts
BUILD_DIR := build/obj
BIN_DIR := build/bin
SRC := $(shell find $(SRC_DIR)/ -name '*.cpp')
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))
DEP := $(OBJ:.o=.d)

TARGET := $(BIN_DIR)/guessnumber

BUILD_TYPE ?= debug
ifeq ($(BUILD_TYPE), release)
	CXXFLAGS += -O2
else
	CXXFLAGS += -g -O0
endif

CXXFLAGS += -I include
CXXFLAGS += -I third_party

.PHONY: default
default: all

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "\033[0;32mBuild complete!\033[0m"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -MMD -MP $< -o $@

-include $(DEP)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(BIN_DIR)/*
	@echo "Cleaned build artifacts"

.PHONY: run
run: $(TARGET)
	@./$(TARGET) 2>/dev/null

.PHONY: debug
debug: $(TARGET)
	@./$(TARGET)

.PHONY: install
install:
	@echo "Running install script..."
	@./$(SCRIPTS_DIR)/install.sh

.PHONY: uninstall
uninstall:
	@echo "Running uninstall script..."
	@./$(SCRIPTS_DIR)/uninstall.sh

.PHONY: uninstall-all
uninstall-all:
	@echo "Running uninstall script..."
	@./$(SCRIPTS_DIR)/uninstall.sh
	@./$(SCRIPTS_DIR)/delete_data.sh

.PHONY: help
help:
	@echo "Usage:"
	@echo "  make                     Build the project (debug mode)"
	@echo "  make BUILD_TYPE=release  Build optimized"
	@echo "  make run                 Build and run"
	@echo "  make debug               Build and run with log in console"
	@echo "  make install             Run install script"
	@echo "  make uninstall           Run uninstall script"
	@echo "  make uninstall-all       Uninstall game and delete datas"
	@echo "  make clean               Remove build artifacts"
	@echo "  make help                Show this help"
# Author: Nguyen-Hanh Nong
# Date: 2022-12-30
# This is a Linux/Unix Makefile for the Library Management Application

# Location of the different directories for the source files, object files, and the executable
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Compiler and linker
COMPILER := g++

# Name of the executable
EXE := $(BIN_DIR)/LibraryManagementApplication

# List of all the source files
SRC := $(wildcard $(SRC_DIR)/*.cc)

# List of all the object files
OBJ := $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRC))

# Flags for the compiler
CXXFLAGS := -Iinclude -Wall -g -MMD -MP

# Commands that we do not want to be created as directories
.PHONY: all clean

# Default target
all: $(EXE)

# Linking the executable
$(EXE): $(OBJ) | $(BIN_DIR)
	$(COMPILER) $(CXXFLAGS) -o $@ $^

# Compiling the source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(COMPILER) $(CXXFLAGS) -c -o $@ $<

# Creating the directories for the object files and the executable if they do not exist
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Cleaning the object files and the executable
clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

# Including the dependency files
-include $(OBJ:.o=.d)
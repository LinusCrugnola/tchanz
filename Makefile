# macros
CXX := g++
CXXFLAGS := -g -Wall -std=c++11
CXXOBJFLAGS := $(CXXFLAGS) -c
LDLIBS := `pkg-config --libs gtkmm-3.0`
LINKING := `pkg-config --cflags gtkmm-3.0`

# directories (comment for release)
OBJ_DIR := obj
TST_DIR := test
SRC_DIR := src

# get files
SRC := $(notdir $(shell find . -maxdepth 1 -name "*.cc" ))
BASE := $(basename $(SRC))
OBJ := $(BASE:%=$(OBJ_DIR)/%.o)
TST := $(shell find $(TST_DIR) -name "*.cc")
BASE_TST := $(notdir $(basename $(TST)))
TST_OBJ := $(addprefix $(TST_DIR)/,$(BASE_TST:%=$(OBJ_DIR)/%.o))
TARGET_OBJ := $(OBJ_DIR)/projet.o
TARGET_TST_OBJ := $(TST_DIR)/$(OBJ_DIR)/test.o

# define target
TARGET_NAME := projet
TARGET := ./$(TARGET_NAME)

# test target
TARGET_TST := test.out

# Build target
$(TARGET): $(OBJ) $(TARGET_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# compile object files
$(OBJ_DIR)/%.o: %.cc %.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXOBJFLAGS) $< -o $@ $(LINKING)

# build tests
$(TARGET_TST): $(TST_OBJ) $(OBJ) $(TARGET_TST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

$(TST_DIR)/obj/%.o: $(TST_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXOBJFLAGS) $< -o $@ $(LINKING)

# compile root files with main()
$(TARGET_OBJ) : projet.cpp
	$(CXX) $(CXXOBJFLAGS) $< -o $@ $(LINKING)

$(TARGET_TST_OBJ) : test.cpp
	$(CXX) $(CXXOBJFLAGS) $< -o $@ $(LINKING)

testfiles: $(TARGET)
	@./runtestfiles.sh
	@make clean

runtests: $(TARGET_TST)
	@./test.out
	@make clean

.PHONY: clean
clean:
	@rm -rf $(TST_DIR)/$(OBJ_DIR)/*
	@rm -rf $(OBJ_DIR)/*
	@rm -f ./*.o
	@rm projet
	@rm test.out
	@echo CLEAN
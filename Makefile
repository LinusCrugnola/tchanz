# macros
CXX := g++
CXXFLAGS := -g -Wall -std=c++11
CXXOBJFLAGS := $(CXXFLAGS) -c
LDFLAGS := -lm 'pkg-config gtkmm-3.0 --libs'
LDLIBS := 'pkg-config gtkmm-3.0 --cflags'

# directories (comment for release)
OBJ_DIR := obj
TST_DIR := test

# get files
SRC := $(notdir $(shell find . -maxdepth 1 -name "*.cc" ))
BASE := $(basename $(SRC))
OBJ := $(BASE:%=$(OBJ_DIR)/%.o)
TST := $(shell find $(TST_DIR) -name "*.cc")
BASE_TST := $(notdir $(basename $(TST)))
TST_OBJ := $(addprefix $(TST_DIR)/,$(BASE_TST:%=$(OBJ_DIR)/%.o))

# define target
TARGET_NAME := projet
TARGET := ./$(TARGET_NAME)

# test target
TARGET_TST := test.out

# Build target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ 
#$(LDFLAGS)

# compile object files
$(OBJ_DIR)/%.o: %.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXOBJFLAGS) $< -o $@ 
#$(LDLIBS)

# build tests
$(TARGET_TST): $(TST_OBJ) $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ 
#$(LDFLAGS)

$(TST_DIR)/obj/%.o: $(TST_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXOBJFLAGS) $< -o $@ 
#$(LDLIBS)	


testfiles: $(TARGET)
	@./runtestfiles.sh
	@make clean

runtests: $(TARGET_TST)
	@make test
	@./test
	@make clean

.PHONY: clean
clean:
	@rm -rf $(TST_DIR)/$(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -f ./*.o
	@rm projet
	@rm test.out
	@echo CLEAN
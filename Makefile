# macros
CXX := g++
CXXFLAGS := -g -Wall -std=c++11
CXXOBJFLAGS := $(CXXFLAGS) -c

# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
TST_PATH := test

# compile macros
TARGET_NAME := prog
TARGET := $(BIN_PATH)/$(TARGET_NAME)

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))


# General target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CXX) $(CXXOBJFLAGS) -o $@ $<

$(OBJ_PATH)/%.o: $(TST_PATH)%.c*
	$(CXX) $(CXXOBJFLAGS) -o $@ $<


# Rules for testfiles
bin/test_squarecell : obj/test_squarecell.o obj/squarecell.o obj/error_squarecell.o
	$(CXX) $(CXXFLAGS) -o $@ obj/test_squarecell.o obj/squarecell.o obj/error_squarecell.o

obj/test_squarecell.o : test/test_squarecell.cc
	$(CXX) $(CXXOBJFLAGS) -o $@ $<


# ADD THIS
.PHONY: test
test: bin/test_squarecell
	@make runtests

#.PHONY: run tests
runtests:
	@echo Test squarecell:
	@ ./bin/test_squarecell

.PHONY: clean
clean:
	@echo CLEAN
	@rm -f bin/*
	@rm -f obj/*
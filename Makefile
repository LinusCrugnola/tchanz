# macros
CXX := g++
CXXFLAGS := -g -Wall -std=c++11
CXXOBJFLAGS := $(CXXFLAGS) -c

# path macros
# BIN_PATH := bin
# OBJ_PATH := obj
# SRC_PATH := src
# TST_PATH := test

# compile macros
TARGET_NAME := prog
TARGET := ./$(TARGET_NAME)

# src files & obj files
# SRC := $(foreach x, ./, $(notdir $(wildcard $(addprefix $(x)*,.c*))))
# OBJ := $(shell find -ipath 'test*.cc' $(addsuffix .o, $(notdir $(basename $(SRC)))))
# TST := $(wildcard test*.cc)
# TAR_SRC := $(SRC) - $(TST)

# General target
$(TARGET): anthill.o ants.o error_squarecell.o message.o nutrition.o project.o simulation.o squarecell.o
	$(CXX) $(CXXFLAGS) -o $@ anthill.o ants.o error_squarecell.o message.o nutrition.o project.o simulation.o squarecell.o

$%.o: %.c*
	$(CXX) $(CXXOBJFLAGS) -o $@ $<


# Rules for testfiles
bin/test_squarecell : test_squarecell.o squarecell.o error_squarecell.o
	$(CXX) $(CXXFLAGS) -o $@ test_squarecell.o squarecell.o error_squarecell.o

bin/test_nutrition : test_nutrition.o squarecell.o error_squarecell.o nutrition.o message.o
	$(CXX) $(CXXFLAGS) -o $@ test_nutrition.o squarecell.o error_squarecell.o nutrition.o message.o


obj/test_squarecell.o : test_squarecell.cc
	$(CXX) $(CXXOBJFLAGS) -o $@ $<

obj/test_nutrition.o : test_nutrition.cc
	$(CXX) $(CXXOBJFLAGS) -o $@ $<


# ADD THIS
.PHONY: test
test: bin/test_squarecell bin/test_nutrition
	@make runtests

#.PHONY: run tests
runtests:
	@echo Test squarecell:
	@ ./test_squarecell
	@ ./test_nutrition

.PHONY: clean
clean:
	@echo CLEAN
	@rm -f ./*.o
	@rm -f prog
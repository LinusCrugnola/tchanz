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
TST := $(foreach x, $(TST_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ_TST := $(addsuffix .o, $(basename $(TST)))

TARGET_TST := $(addprefix $(BIN_PATH)/, $(basename $(notdir $(TST))))


# clean files list
DISTCLEAN_LIST := $(OBJ)
CLEAN_LIST := $(TARGET) \
			  $(DISTCLEAN_LIST) \
			  $(OBJ_TST)

# default rule
default: makedir all

# non-phony targets
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


.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

.PHONY: all
all: $(TARGET)

# ADD THIS
.PHONY: test
test: 
	@make $(TARGET_TST)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)
	@rm -f bin/*
	@rm -f obj/*	

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)
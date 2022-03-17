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
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG)
CLEAN_LIST := $(TARGET) \
			  $(TARGET_DEBUG) \
			  $(DISTCLEAN_LIST)

# default rule
default: makedir all

# non-phony targets
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CXX) $(CXXOBJFLAGS) -o $@ $<

$(TST_PATH)/%.o: $(TST_PATH)%.c*
	$(CXX) $(CXXOBJFLAGS) -o $@ $<

bin/test_squarecell : test/test_squarecell.o obj/squarecell.o
	$(CXX) $(CXXFLAGS) -o $@ test/test_squarecell.o obj/squarecell.o




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

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)
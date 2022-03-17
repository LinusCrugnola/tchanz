CXX     = g++
CXXFLAGS = -g -Wall -std=c++11

# folders:
TARGET := bin/prog
OBJ_DIR := obj
SRC_DIR := src
TEST_DIR := test


# Chercher les files:
CXXFILES := $(shell find $(SRC_DIRS) -name '*.cc' -or -name '.cpp')
OFILES := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(CXXFILES)))))

INCLUDE_DIR := $(shell find $(SRC_DIR) -type d)
INCLUDE_FLAGS := $(addprefix -I,$(INCLUDE_DIR))


# Build le exe:
$(TARGET): $(OFILES)
	$(CXX) $(OFILES) -o $(TARGET)

# Build les obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c*
	$(CXX) $(CXXFILES) -c -o $(OFILES)


depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f ./obj/*.o ./bin/* ./src/*.o

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
error_squarecell.o: src/error_squarecell.cc src/error_squarecell.h
message.o: src/message.cc src/message.h
project.o: src/project.cc
squarecell.o: src/squarecell.cc

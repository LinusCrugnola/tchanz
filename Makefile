CXX     = g++
CXXFLAGS = -g -Wall -std=c++11

# folders:
TARGET := bin/prog
OBJ_DIR := obj
SRC_DIR := ./src
TEST_DIR := test


# Chercher les files:
CXXFILES := $(shell find $(SRC_DIRS) -name '*.cc' -or -name '.cpp')
OFILES := $(CXXFILES:.cc = .o)


# Build le exe:
$(TARGET): $(OFILES)
	$(CXX) $(OFILES) -o $(TARGET)

# Build les obj
$(OFILES): $(CXXFILES)
	$(CXX) $(CXXFLAGS) -c $(CXXFILES)


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

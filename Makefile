# macros
CXX := g++
CXXFLAGS := -g -Wall -std=c++11
CXXOBJFLAGS := $(CXXFLAGS) -c


# compile macros
TARGET_NAME := projet
TARGET := ./$(TARGET_NAME)

# General target
$(TARGET): anthill.o ants.o error_squarecell.o message.o nutrition.o projet.o simulation.o squarecell.o
	$(CXX) $(CXXFLAGS) -o $@ anthill.o ants.o error_squarecell.o message.o nutrition.o projet.o simulation.o squarecell.o

$%.o: %.c*
	$(CXX) $(CXXOBJFLAGS) -o $@ $<


# Rules for testfiles
test/test_squarecell : test_squarecell.o squarecell.o error_squarecell.o
	@mkdir -p test
	$(CXX) $(CXXFLAGS) -o $@ test_squarecell.o squarecell.o error_squarecell.o

test/test_nutrition : test_nutrition.o squarecell.o error_squarecell.o nutrition.o message.o
	@mkdir -p test
	$(CXX) $(CXXFLAGS) -o $@ test_nutrition.o squarecell.o error_squarecell.o nutrition.o message.o


test_squarecell.o : test_squarecell.cc
	$(CXX) $(CXXOBJFLAGS) -o $@ $<

test_nutrition.o : test_nutrition.cc
	$(CXX) $(CXXOBJFLAGS) -o $@ $<


# ADD THIS
.PHONY: test
test: test/test_squarecell test/test_nutrition
	@make runtests
	@rm -rf test
	@make clean

testfiles: $(TARGET)
	@./runtestfiles.sh
	@make clean

runtests:
	@echo Test squarecell:
	@ ./test/test_squarecell
	@ ./test/test_nutrition

.PHONY: clean
clean:
	@echo CLEAN
	@rm -f ./*.o
	@rm -f $(TARGET)
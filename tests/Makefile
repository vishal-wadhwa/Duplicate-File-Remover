CXX = g++
IDIR = ../include
ODIR = obj
LDIR = ../lib
TDIR = ../tests
SRC = ../src
LDFLAGS = -lcrypto -lboost_filesystem -lboost_system -lcppunit
CXXFLAGS = -I$(IDIR) -std=c++14 -Wall -pedantic -Wextra -DDEBUG

_DEPS = file_handler.h file_hash.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS)) #DEPENDENCIES

_DEPS_TEST = unit_tests.h
DEPS_TEST = $(patsubst %, $(TDIR)/%, $(_DEPS_TEST))

_OBJ = file_hash.o file_handler.o unit_tests.o test.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

# _DEPS_TEST = test.h
# DEPS_TEST = $(patsubst %, $(TDIR)/%, $(_DEPS_TEST))

$(ODIR)/%.o: $(SRC)/%.cpp $(DEPS) #DEPS ensures that if DEPS change then recompile
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/%.o: $(TDIR)/%.cpp $(DEPS_TEST)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# $(ODIR)/test.o: test.cpp
# 	$(CXX) -c -o $@ $< $(CXXFLAGS)

test: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

run:
	./test

.PHONY: clean

clean:
	/bin/rm -f $(ODIR)/*.o test
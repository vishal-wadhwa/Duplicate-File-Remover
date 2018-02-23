CXX = g++ 
IDIR = ../include
ODIR = obj
LDIR = ../lib
LDFLAGS = -lcrypto -lboost_filesystem -lboost_system
CXXFLAGS = -I$(IDIR) -std=c++14 -Wall -pedantic -Wextra

_DEPS = file_handler.h file_hash.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS)) #DEPENDENCIES

_OBJ = file_hash.o file_handler.o main.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS) #DEPS ensures that if DEPS change then recompile
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

run:
	./test
.PHONY: clean

clean:
	/bin/rm -f $(ODIR)/*.o main
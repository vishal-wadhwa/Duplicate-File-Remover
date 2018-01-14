CC = g++ 
IDIR = ../include
ODIR = obj
LDIR = ../lib
TDIR = ../tests
LIBS = -lcrypto -lboost_filesystem -lboost_system
CFLAGS = -I$(IDIR) -std=c++14 -Wall -pedantic -Wextra

_DEPS = file_handler.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS)) #DEPENDENCIES

_OBJ = main.o file_handler.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	/bin/rm -f $(ODIR)/*.o
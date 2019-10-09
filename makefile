
CC=gcc
CFLAGS=-lm

ODIR=obj
LDIR=../libs
LIBS=-lm

_DEPS = main.c Compression/compression.h Records/records.h Encryption/encryption.h Interface/interface.h Containers/Vector/vector.h
DEPS = $(patsubst %,$(LDIR)/%,$(_DEPS))
OBJ = main.o libs/Compression/compression.o libs/Records/records.o libs/Encryption/encryption.o libs/Interface/interface.o libs/Containers/Vector/vector.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

MECD: $(OBJ)
	$(CC) -Wall -ansi -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
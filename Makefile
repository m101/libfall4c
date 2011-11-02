EXEC=vigenere

CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-lunac

FALL4C=dictionnary.o string_ext.o
OBJS=vigenere.o stats.o main.o util/errors.o $(FALL4C)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(EXEC)

# files
LIB_NAME=libutil
INCLUDE_DIR=../util
SRC=debug.c errors.c
OBJS=$(SRC:.c=.o)

# compilation flags
CC=gcc
CFLAGS=-g -Wall -I$(INCLUDE_DIR)
LDFLAGS=

all: lib_static lib_shared

%.o: %.c
	$(CC) -fPIC -o $@ -c $< $(CFLAGS) $(LDFLAGS)

lib_static: $(OBJS)
	ar rcs $(LIB_NAME).a $^

lib_shared: $(OBJS)
	$(CC) -shared -Wl,-soname,$(LIB_NAME).so.1 -o $(LIB_NAME).so.1.0.1 $^

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(LIB_NAME).so.1.0.1
	rm *.a

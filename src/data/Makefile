# files
LIB_NAME=libdata
INCLUDE=
SRC=array_associative.c dictionnary.c queue.c tree_redblack.c				   \
	array_manipulation.c dictionnary_example.c list.c stack.c tree_binary.c	   \
	tree_common.c tree_sparse.c
OBJS=$(SRC:.c=.o)

# sub projects
SUB_PROJ=

# compilation flags
CC=gcc
CFLAGS=-g -Wall $(INCLUDE)
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

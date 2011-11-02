# files
LIB_NAME=libmath
INCLUDE_DIR=../util
SRC=bases.c geometry_space.c math_basic.c math_ext.c math_probability.c \
	math_trigonometry.c dl.c interpolation.c math_complex_numbers.c		\
	math_matrix.c math_sequence.c vector_space.c
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

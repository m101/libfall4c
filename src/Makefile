# files
LIB_NAME=libfall4c
INCLUDE=-Idata -Iutil -Imath
SRC=collision.c  ctype_extended.c  fileBrowse.c  file.c string_ext.c
OBJS=$(SRC:.c=.o)

# sub projects
SUB_PROJ=math util

# compilation flags
CC=gcc
CFLAGS=-g -Wall $(INCLUDE)
LDFLAGS=

all: lib_static lib_shared subs

%.o: %.c
	$(CC) -fPIC -o $@ -c $< $(CFLAGS) $(LDFLAGS)

lib_static: $(OBJS)
	ar rcs $(LIB_NAME).a $^

lib_shared: $(OBJS)
	$(CC) -shared -Wl,-soname,$(LIB_NAME).so.1 -o $(LIB_NAME).so.1.0.1 $^

subs:
	cd math && $(MAKE)
	cd util && $(MAKE)

.PHONY: clean mrproper

clean:
	cd math && $(MAKE) clean
	cd util && $(MAKE) clean
	rm *.o

mrproper: clean
	cd math && $(MAKE) mrproper
	cd util && $(MAKE) mrproper
	rm $(LIB_NAME).so.1.0.1
	rm *.a

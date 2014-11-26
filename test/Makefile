CFLAGS= \
		-Wall \
		-g \
		-pthread

DEPS= \
	  list.h \
	  map.h \
	  clientserver.h \
	  ../client.o \
	  ../server.o \
	  pairparser.h \
	  ../pairparser.o \
	  matrix.h

all: test

test: test.c $(DEPS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o

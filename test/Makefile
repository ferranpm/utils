CFLAGS= \
		-Wall \
		-g

DEPS= \
	  list.h \
	  map.h \
	  pairparser.h \
	  ../pairparser.o

all: test

test: test.c $(DEPS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o

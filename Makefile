CFLAGS= \
		-Wall \
		-g

LIBS= \
	 pairparser.o

all: $(LIBS) tests

tests:
	rm -f test/test
	make -C test

pairparser.o: pairparser.c pairparser.h map.h
	$(CC) $(CFLAGS) -c pairparser.c

clean:
	rm -rf *.o

CFLAGS=-Wall

LIBS= \
	 server.o \
	 client.o \
	 pairparser.o

all: $(LIBS)

tests: $(TESTS)

*.o: $(@:.o=.c) $(@:.o=.h)
	$(CC) $(CFLAGS) -c $(@:.o=.c) -g

clean:
	rm *.o

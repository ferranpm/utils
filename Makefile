CFLAGS= \
		-Wall \
		-g

LIBS= \
	 server.o \
	 client.o \
	 pairparser.o

all: $(LIBS)

server.o: server.c server.h
	$(CC) $(CFLAGS) -pthread -c server.c

client.o: client.c client.h
	$(CC) $(CFLAGS) -c client.c

pairparser.o: pairparser.c pairparser.h
	$(CC) $(CFLAGS) -c pairparser.c

clean:
	rm *.o

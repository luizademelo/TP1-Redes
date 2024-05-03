all: 
	gcc -Wall -c common.c
	gcc -Wall server.c common.o  -o server
	gcc -Wall client.c common.o  -o client

clean: 
	rm -f client 
	rm -f server
	rm -f *.o
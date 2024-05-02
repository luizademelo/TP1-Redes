all: 
	gcc -Wall -c common.c
	gcc -Wall server.c common.o -lm -o server
	gcc -Wall client.c common.o -lm -o client

clean: 
	rm client 
	rm server
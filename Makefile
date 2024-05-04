all: 
	gcc -Wall -c common.c -lm 
	gcc -Wall server.c common.o  -o ./bin/server -lm
	gcc -Wall client.c common.o  -o ./bin/client -lm

clean: 
	rm -f client 
	rm -f server
	rm -f *.o
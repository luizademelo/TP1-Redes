all: 
	gcc -Wall -c common.c -o ./obj/common.o -lm 
	gcc -Wall server.c ./obj/common.o  -o ./bin/server -lm
	gcc -Wall client.c ./obj/common.o  -o ./bin/client -lm

clean: 
	rm -f ./bin/client 
	rm -f ./bin/server
	rm -f ./obj/*.o
build: 
	gcc server.c -lm -o server
	gcc client.c -o client

clean: 
	rm client 
	rm server
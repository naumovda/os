all: socket2-server socket2-client

socket2-server: socket2-server.c
	gcc -o $@ $^

socket2-client: socket2-client.c
	gcc -o $@ $^

clean:
	rm -f socket2-server socket2-client

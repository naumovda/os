all: socket3-server socket3-client

socket3-server: socket3-server.c
	gcc -o $@ $^

socket3-client: socket3-client.c
	gcc -o $@ $^

clean:
	rm -f socket3-server socket3-client

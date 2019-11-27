all: fifo2-server fifo2-client

fifo2-server: fifo2-server.c
	gcc -o $@ $^

fifo2-client: fifo2-client.c
	gcc -o $@ $^

clean:
	rm -f fifo2-server fifo2-client

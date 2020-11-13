all: shm2-owner shm2-user

shm2-owner: shm2-owner.c
	gcc -o $@ $^

shm2-user: shm2-user.c
	gcc -o $@ $^

clean:
	rm -f shm2-owner shm2-user

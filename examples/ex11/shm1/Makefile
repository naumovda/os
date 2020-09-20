all: shm1-owner shm1-user

shm1-owner: shm1-owner.c
	gcc -o $@ $^

shm1-user: shm1-user.c
	gcc -o $@ $^

clean:
	rm -f shm1-owner shm1-user

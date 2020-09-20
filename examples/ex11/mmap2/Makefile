all: mmap2-owner mmap2-user

mmap2-owner: mmap2-owner.c
	gcc -o $@ $^

mmap2-user: mmap2-user.c
	gcc -o $@ $^

clean:
	rm -f mmap2-owner mmap2-user

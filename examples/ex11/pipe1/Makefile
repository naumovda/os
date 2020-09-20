all: pipe1-parent pipe1-src pipe1-dst

pipe1-parent: pipe1-parent.c
	gcc -o pipe1-parent pipe1-parent.c

pipe1-src: pipe1-src.c
	gcc -o pipe1-src pipe1-src.c

pipe1-dst: pipe1-dst.c
	gcc -o pipe1-dst pipe1-dst.c

clean:
	rm -f pipe1-parent pipe1-src pipe1-dst

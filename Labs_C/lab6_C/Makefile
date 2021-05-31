all:	build clean run

build:	lab6_C.o Tree.o
	gcc lab6_C.o Tree.o -o YASS

lab6_C.o:	lab6_C.c
	gcc  -c lab6_C.c -lm -std=c89

Tree.o: 	Tree.c
	gcc -c Tree.c -lm -std=c89

run:	build
	./YASS.exe

clean:	build
	del lab6_C.o Tree.o
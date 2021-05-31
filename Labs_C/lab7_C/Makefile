all:	build clean run

build:	lab7_C.o
	gcc lab7_C.o -o YEP

lab7_C.o:	lab7_C.c
	gcc  -c lab7_C.c -lm -std=c89

run:	build
	./YEP.exe

clean:	build
	del lab7_C.o
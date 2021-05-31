all:	lab5
	./YASS.exe

lab5:	lab5_C.o ListFuncs.o
	g++ lab5_C.o ListFuncs.o -o YASS
	del lab5_C.o ListFuncs.o

lab5_C.o:	lab5_C.c
		g++  -c lab5_C.c -lm -std=c89

ListFuncs.o: 	ListFuncs.c
		g++ -c ListFuncs.c -lm -std=c89

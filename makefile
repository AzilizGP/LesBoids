test.out: main.o bwindow.o Bird.o
	g++ -o test.out main.o bwindow.o Bird.o -lX11 -L/usr/X11R6/lib
main.o: main.cpp
	g++ -c main.cpp 
bwindow.o: bwindow.cpp bwindow.h
	g++ -c bwindow.cpp
Bird.o: Bird.cpp Bird.h 	
	g++ -c Bird.cpp
clean :
	rm *.o *.out

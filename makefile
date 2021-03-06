test.out: main.o bwindow.o Boid.o Bird.o Obstacle.o
	g++ -g -o test.out main.o bwindow.o Boid.o Bird.o Obstacle.o -lX11 -L/usr/X11R6/lib
main.o: main.cpp
	g++ -g -c main.cpp 
bwindow.o: bwindow.cpp bwindow.h
	g++ -g -c bwindow.cpp
Boid.o: Boid.cpp Boid.h 	
	g++ -g -c Boid.cpp
Bird.o: Bird.cpp Bird.h
	g++ -g -c Bird.cpp
Obstacle.o: Obstacle.cpp Obstacle.h
	g++ -g -c Obstacle.cpp

clean :
	rm *.o *.out

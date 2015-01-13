#include <stdio.h>
#include "bwindow.h"
#include "Boid.h"
#include <cstdlib>
#include "Bird.h"
#include <cmath>

/*
double v1x(void);
double v2x(void);
double v3x(void);
double vxevol(void);
double v1y(void);
double v2y(void);
double v3y(void);
double vyevol(void);

double distance(Bird bird1, Bird bird2);      // calculates the distance between 2 birds
*/

int main()
{
	srand(time(NULL));
	int i=12;
//	test bird
	Bird piaf;
	printf("piaf : x=%f & y=%f\n",piaf._x(),piaf._y());
	Bird oiseau;
	printf("oiseau : x=%f & y=%f\n",oiseau._x(),oiseau._y());
	
//	test boid
	Boid popu;
	int m=popu.N;
	Bird* piti = new Bird[m]; 
	Bird* poutou = popu._population();
	Bird labous;
	labous=popu[2];
	printf("labous : x=%f & y=%f\n",labous._x(),labous._y());

//	test birds number
	printf("Birds numbers\n");
	printf("N=%d\n",popu.N);
	printf("K=%d\n",popu._K(i));
	printf("Kprim=%d\n",popu._Kprim(i));
	
//	test obstacles
	Obstacle* obs = popu._obstacles();
	printf("obstacle : x=%f & y=%f\n",obs[1]._x(),obs[1]._y());
	

//  test v1
	printf("oiseau n°%d : v1x=%lg & v1y=%lg\n",i,popu.v1x(i),popu.v1y(i));
//  test v2
	printf("oiseau n°%d : v2x=%lg & v2y=%lg\n",i,popu.v2x(i),popu.v2y(i));
//  test v3
	printf("oiseau n°%d : v3x=%lg & v3y=%lg\n",i,popu.v3x(i),popu.v3y(i));
//	test vevol
	printf("oiseau n°%d : vxevol=%lg & vyevol=%lg\n",i,popu.vxevol(i),popu.vyevol(i));

	
/*
    bwindow win(640,480);
    printf("%d\n",win.init());
    win.map();
    for(;;)
    {
	int ev = win.parse_event();
	switch(ev)
		{
			case BKPRESS :
			printf("keypressed\n"); 
			printf("key : %s\n",win.get_lastkey());
			break;
			case BBPRESS:
			printf("buttonpressed\n"); break;
			case BEXPOSE:
			printf("expose\n"); break;
			case BCONFIGURE:
			printf("configure\n"); break;
		}
	win.draw_point(100,100,0xFF00);
	win.draw_line(100,100,200,200,0xFF0000);
	win.draw_text(10,10,0x0,"Hello World",strlen("Hello World"));
	win.draw_square(200,200,220,220,0xFF00);
	win.draw_fsquare(400,400,440,440,0xFF00);
    }
*/
    return 0;
}

#include <stdio.h>
#include "bwindow.h"
#include "Boid.h"
#include <cstdlib>
#include "Bird.h"
#include <cmath>

/*
faire bouger les oiseaux
leur rajouter une queue
attention : des oiseaux sont créer au même endroit que des obstacles...
créer du vent, des prédateurs
*/

int main()
{
	srand(time(NULL));

	int i=2;
//	test bird
	Bird piaf;
	printf("piaf : x=%f & y=%f\n",piaf._x(),piaf._y());
	printf("dt = %f\n",piaf.dt);
	
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
// 	test v4
	printf("oiseau n°%d : v4x=%lg & v4y=%lg\n",i,popu.v4x(i),popu.v4y(i));
//	test v
	printf("oiseau n°%d : vx=%lg & vy=%lg\n",i,popu.vx(i),popu.vy(i));
//  test predator
	printf("predator : x=%f & y=%f\n",popu._predator()._x(), popu._predator()._y());
	printf("predator : vx=%f & vy=%f\n", popu.vpredx(), popu.vpredy());
//	printf("predator : vpx=%f & vpy=%f\n",popu._vpx(),popu._vpy());
// test prey
	printf("prey : x=%f & y=%f\n", popu.preyx(), popu.preyy() );


	



	int W=800;
	int H=800;
    bwindow win(W,H);
    printf("%d\n",win.init());
    win.map();
		
	Boid population;
   	int k;
   	double* x = new double[population.N];
   	double* y = new double[population.N];
   	double* vx = new double[population.N];
   	double* vy = new double[population.N];
	for(k=0;k<population.N;k++)
	{
		x[k] = population[k]._x();
		y[k] = population[k]._y();
	}
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
//		win.draw_text(10,10,0x0,"Hello World",strlen("Hello World"));
//		win.draw_line(100,100,200,200,0xFF0000);          // queue de l'oiseau
//		win.draw_square(200,200,220,220,0xFF00);          // tête de l'oiseau
//		win.draw_fsquare(400,400,440,440,0xFF00);          // obstacle

// dessin des obstacles
			for(k=0;k<population.P;k++)
			{
				win.draw_fsquare(population._obstacles()[k]._x() - 5, population._obstacles()[k]._y() - 5, 
				population._obstacles()[k]._x() + 5, population._obstacles()[k]._y() + 5, 0xFF0);
			}
// dessin de la population
			for(k=0;k<population.N;k++)
			{ 
				win.draw_square(x[k], y[k], x[k] + 5, y[k] + 5, 0xFF00);
				win.draw_line(x[k], y[k], x[k]-population.vx(k), y[k]-population.vy(k), 0xFF0000); 

				x[k] = x[k] + population[k]._dt() * population.vx(k);
				y[k] = y[k] + population[k]._dt() * population.vy(k);
			}
// dessin du prédateur
/*		win.draw_fsquare(population._predator()._x() - 5, population._predator()._y() - 5, population._predator()._x() + 5, population._predator()._y() + 5, 0xFF0000) ;
		population._predator()._x() = population._predator()._x() + population._predator().dt * population.vpredx();
		population._predator()._y() = population._predator()._y() + population._predator().dt * population.vpredy();
*/
    }

    return 0;
}
/*
int wind(Boid pop, int k)
{
	if(pop[k]._x() < 50 || pop[k]._x() > 800 - 50)
	{
		
	}
	if(pop[k]._y() < 50 || pop[k]._y() > 800 - 50)
	{
		
	}
}
*/

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

	int i=5;
	int j=0;
/*
//	test bird
	Bird piaf;
	printf("piaf : x=%f & y=%f\n",piaf._x(),piaf._y());
	printf("dt = %f\n",piaf.dt);
*/	
//	test boid
	Boid popu;
/*	int m=popu.N;
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
*/
for(i=0;i<5;i++)
{
//  test v1
	printf("oiseau n°%d : v1x=%lg & v1y=%lg\n",i,popu.v1x(i),popu.v1y(i));
//  test v2
	printf("oiseau n°%d : v2x=%lg & v2y=%lg\n",i,popu.v2x(i),popu.v2y(i));
//  test v3
	printf("oiseau n°%d : v3x=%lg & v3y=%lg\n",i,popu.v3x(i),popu.v3y(i));
	for(j=0;j<popu.P;j++)
	{
		printf("distance bird n°%d to obstacle n°%d = %g\n",i,j,sqrt( (popu._obstacles()[j]._x()-popu[i]._x())*(popu._obstacles()[j]._x()-popu[i]._x()) + (popu._obstacles()[j]._y()-popu[i]._y())*(popu._obstacles()[j]._y()-popu[i]._y()) ) );
	}
// 	test v4
	printf("oiseau n°%d : v4x=%lg & v4y=%lg\n",i,popu.v4x(i),popu.v4y(i));
//	test v
	printf("oiseau n°%d : vx=%lg & vy=%lg\n",i,popu.vx(i),popu.vy(i));
//	test coordinates evolution
	printf("bird n°%d coordinates at t time : x=%f & y=%f\n",i, popu[i]._x(), popu[i]._y());
	printf("bird n°%d coordinates at t+dt : x=%f & y=%f\n\n",i, popu.xevol(i), popu.yevol(i));
}
/*
//  test predator
	printf("predator coordinates at t time : x=%f & y=%f\n",popu._predator()._x(), popu._predator()._y());
	printf("predator coordinates at t+dt : x=%f & y=%f\n",popu.xpredevol(), popu.ypredevol());	
	printf("predator : x=%f & y=%f\n",popu._predator()._x(), popu._predator()._y());
	printf("predator : vx=%f & vy=%f\n", popu.vpredx(), popu.vpredy());
	printf("predator's speed by default when hunting : vpx=%f & vpy=%f\n",popu._vpx(),popu._vpy());
//	test predator - obstacles
	printf("obstacles next to predator : %d\n",popu._Opred());
	printf("obstacles influence on the predator's speed : vobsx=%f & vobsy=%f\n", popu.vpredox(), popu.vpredoy());
// test prey
	printf("closest prey to predator : x=%f & y=%f\n", popu.preyx(), popu.preyy() );
//	test prey index
	printf("closest prey index = %d\n",popu.preyindex());
*/




	Boid population;
	
	int W = population.W;
	int H = population.H;

	bwindow win(W,H);
    printf("%d\n",win.init());
    win.map();
	
   	int k;
   	double* x = new double[population.N];
   	double* y = new double[population.N];
   	double* vx = new double[population.N];
   	double* vy = new double[population.N];
   	double predx = population._predator()._x();
	double predy = population._predator()._y();
	for(k=0;k<population.N;k++)
	{
		x[k] = population[k]._x();
		y[k] = population[k]._y();
		vx[k] = population.vx(k);
		vy[k] = population.vy(k);
				
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
//		win.draw_point(100,100,0xFF00);
//		win.draw_text(10,10,0x0,"Hello World",strlen("Hello World"));
//		win.draw_line(100,100,200,200,0xFF0000);          // queue de l'oiseau
//		win.draw_square(200,200,220,220,0xFF00);          // tête de l'oiseau
//		win.draw_fsquare(400,400,440,440,0xFF00);          // obstacle

// dessin des obstacles
			for(k=0;k<population.P;k++)
			{
				win.draw_fsquare(population._obstacles()[k]._x() - 5, population._obstacles()[k]._y() - 5, population._obstacles()[k]._x() + 5, population._obstacles()[k]._y() + 5, 0xFF0);
			}
// nettoie l'écran pour les birds
			for(k=0;k<population.N;k++)
			{ 
				win.draw_fsquare(x[k]-3, y[k]-3, x[k] + 3, y[k] + 3,0xFEFEFE);
			}	
// dessin de la population
			for(k=0;k<population.N;k++)
			{ 
				x[k] += population.xevol(k);
				y[k] += population.yevol(k);
				win.draw_square(x[k]-2, y[k]-2, x[k] + 2, y[k] + 2, 0xFF00);

			}

// nettoie l'écran pour le prédateur
		win.draw_fsquare(predx - 3, predy - 3, predx + 3, predy + 3, 0xFEFEFE) ;
// dessin du prédateur
		predx += population.predator.dt * population.vpredx();
		predy += population.predator.dt * population.vpredy();
		win.draw_fsquare(predx - 3, predy - 3, predx + 3, predy + 3, 0xFF0000) ;

		usleep(1000);
    }

    return 0;
}

// BORDURE POUR OISEAUX
/*
 				if(x[k]<50 || x[k]>W-50)
				{
				//	x[k] -= population[k].dt * population.vx(k);	
				}
				else
				{
					x[k] += population[k].dt * population.vx(k);
				}
				if(y[k]<50 || y[k]>H-50)
				{
				//	y[k] -= population[k].dt * population.vy(k);
				}
				else
				{
					y[k] += population[k].dt * population.vy(k);
				}
*/

// BORDURE POUR PREDATEUR
/*
		if(predx<50 || predx>W-50)
		{
		//	predx -= population.predator.dt * population.vpredx();
		}
		else
		{
			predx += population.predator.dt * population.vpredx();
		}
		if(predy<50 || predy>H-50)
		{
		//	predy -= population.predator.dt * population.vpredy();
		}
		else
		{
			predy += population.predator.dt * population.vpredy();
		}
*/

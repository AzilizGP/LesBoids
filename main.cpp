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




	Boid pop;

for(i=0;i<5;i++)
{
//  test v1
	printf("oiseau n°%d : v1x=%lg & v1y=%lg\n",i,pop.v1x(i),pop.v1y(i));
//  test v2
	printf("oiseau n°%d : v2x=%lg & v2y=%lg\n",i,pop.v2x(i),pop.v2y(i));
//  test v3
	printf("oiseau n°%d : v3x=%lg & v3y=%lg\n",i,pop.v3x(i),pop.v3y(i));
	for(j=0;j<pop.P;j++)
	{
		printf("distance bird n°%d to obstacle n°%d = %g\n",i,j,sqrt( (pop._obstacles()[j]._x()-pop[i]._x())*(pop._obstacles()[j]._x()-pop[i]._x()) + (pop._obstacles()[j]._y()-pop[i]._y())*(pop._obstacles()[j]._y()-pop[i]._y()) ) );
	}
// 	test v4
	printf("oiseau n°%d : v4x=%lg & v4y=%lg\n",i,pop.v4x(i),pop.v4y(i));
//	test v
	printf("oiseau n°%d : vx=%lg & vy=%lg\n",i,pop.vx(i),pop.vy(i));
//	test coordinates evolution
	printf("bird n°%d coordinates at t time : x=%f & y=%f\n",i, pop[i]._x(), pop[i]._y());
	printf("bird n°%d coordinates at t+dt : x=%f & y=%f\n\n",i, pop.xevol(i), pop.yevol(i));
}

	int W = pop.W;
	int H = pop.H;

	bwindow win(W,H);
    printf("%d\n",win.init());
    win.map();
	
   	int k;

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

// dessin des obstacles
			for(k=0;k<pop.P;k++)
			{
				win.draw_fsquare(pop._obstacles()[k]._x() - 5, pop._obstacles()[k]._y() - 5, pop._obstacles()[k]._x() + 5, pop._obstacles()[k]._y() + 5, 0xFF0);
			}
// nettoie l'écran pour les birds
			for(k=0;k<pop.N;k++)
			{ 
				win.draw_fsquare(pop[k].x - 3, pop[k].y - 3, pop[k].x + 3, pop[k].y + 3,0xFEFEFE);
			}	
// dessin de la population
			for(k=0;k<pop.N;k++)
			{ 
				pop.population[k].x += pop.xevol(k);
				pop.population[k].y += pop.yevol(k);
				win.draw_square(pop.population[k].x - 2, pop.population[k].y - 2, pop.population[k].x + 2, pop.population[k].y + 2, 0xFF00);
			}
// vent
			for(k=0;k<pop.N;k++)
			{ 
				if(pop.population[k].x < 2 )
				{
				pop.population[k].x -= pop.xevol(k);
				}
				if( pop.population[k].x > pop.W -2)
				{
				pop.population[k].x -= pop.xevol(k);
				}
				if(pop.population[k].y < 2 )
				{
				pop.population[k].y -= pop.yevol(k);
				}
				if(pop.population[k].y > pop.H - 2)
				{
				pop.population[k].y -= pop.yevol(k);
				}
			}

// nettoie l'écran pour le prédateur
		win.draw_fsquare(pop.predator.x - 3, pop.predator.y - 3, pop.predator.x + 3, pop.predator.y + 3, 0xFEFEFE) ;
// dessin du prédateur
		pop.predator.x += pop.predator.dt * pop.vpredx();
		pop.predator.y += pop.predator.dt * pop.vpredy();
		win.draw_fsquare(pop.predator.x - 3, pop.predator.y - 3, pop.predator.x + 3, pop.predator.y + 3, 0xFF0000) ;

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

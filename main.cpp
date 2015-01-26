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

	int i;
	int j;

	Boid pop;
	int W = pop.W;
	int H = pop.H;

	printf("Paramètres :\n");
	printf("fenêtre de dimension W=%d & H=%d\n",pop.W, pop.H);
	printf("Nombre d'oiseaux = %d\nNombre d'obstacles = %d\n",pop.N, pop.P);
	printf("Rayon de perception = %g\nRayon de contact = %g\nRayon de perception du prédateur = %g\nRayon de contact du prédateur = %g\n",pop._r(),pop._c(), pop._Rp(), pop._m());
	printf("Vitesse maximum des oiseaux : Vxmax = %g & Vymax = %g\nVitesse maximum du prédateur : Vxmax = %g & Vymax = %g\n",pop[1]._vxmax(), pop[1]._vymax(), pop._vpx(), pop._vpy());

	for(i=0 ; i<10 ; i++)
	{
		printf("nb aléatoire n°%d = %d\n", i, pop.plusoumoins());
	}
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
		
		win.draw_text(pop.W + 100,50,0x0,"Oiseaux morts",strlen("Oiseaux morts"));
				
// dessin des bordures
			win.draw_line(0,0,0,pop.H,0x00FFCC);
			win.draw_line(0,0,pop.W,0,0x00FFCC);
			win.draw_line(0,pop.H,pop.W,pop.H,0x00FFCC);
			win.draw_line(pop.W,0,pop.W,pop.H,0x00FFCC);
			
// dessin des obstacles
			for(k=0;k<pop.P;k++)
			{
				win.draw_fsquare(pop._obstacles()[k]._x() - 3, pop._obstacles()[k]._y() - 3, pop._obstacles()[k]._x() + 3, pop._obstacles()[k]._y() + 3, 0x66FF00);
			}

// nettoie l'écran pour les birds
			for(k=0;k<pop.N;k++)
			{ 
				win.draw_fsquare(pop[k]._x()- 2, pop[k]._y() - 2, pop[k]._x() + 2, pop[k]._y() + 2,0xFEFEFE);
			}	
// dessin de la population
			for(k=0;k<pop.N;k++)
			{ 
				pop.population[k].setx(pop.xevol(k));
				pop.population[k].sety(pop.yevol(k));
				win.draw_square(pop.population[k]._x() - 1, pop.population[k]._y() - 1, pop.population[k]._x() + 1, pop.population[k]._y() + 1, 0x993300);
			}


// nettoie l'écran pour le prédateur
		win.draw_fsquare(pop.predator._x() - 3, pop.predator._y() - 3, pop.predator._x() + 3, pop.predator._y() + 3, 0xFEFEFE) ;
// dessin du prédateur
		pop.predator.setx(pop.xpredevol());
		pop.predator.sety(pop.ypredevol());
		win.draw_fsquare(pop.predator._x() - 3, pop.predator._y() - 3, pop.predator._x() + 3, pop.predator._y() + 3, 0xFF0000) ;

		usleep(1000);
    }


    return 0;
}



/*
A FAIRE
- créer un tableau Nx2 de Birds
- le remplir de xi et yi aléatoires
- définir le rayon de perception par une méthode qui compte le nombre de bird K dans ce cercle
- définir la distance de contact c
- définir les obstacles
- définir v1, v2 et v3
*/


#ifndef __BOID_H__
#define __BOID_H__


// ===========================================================================
//                                  Libraries
// ===========================================================================
#include <cstdio>
#include <cstdlib>
#include "Bird.h"
#include "Obstacle.h"



// ===========================================================================
//                                Project Files
// ===========================================================================




// ===========================================================================
//                              Class declarations
// ===========================================================================

class Boid
{
  public :
    
    // =======================================================================
    //                                 Enums
    // =======================================================================
    
    // =======================================================================
    //                               Constructors
    // =======================================================================
    Boid(void);                            // constructor by default
	Boid( const Boid& boid );
	
    // =======================================================================
    //                                Destructor
    // =======================================================================
    ~Boid(void);

    // =======================================================================
    //                            Accessors: getters
    // =======================================================================

    int _N(void) const;
    int _P(void) const;

	double _r(void) const;
	double _c(void) const;
	double _Rp(void) const;
	double _vpx(void) const;
	double _vpy(void) const;

	Bird* _population(void);
	Obstacle* _obstacles(void);
	Bird _predator(void);
	double _gam1(void) const;
	double _gam2(void) const;
	double _gam3(void) const;
	double _gam4(void) const;

    // =======================================================================
    //                            Accessors: setters
    // =======================================================================

    // =======================================================================
    //                                Operators
    // =======================================================================
	    
	Bird operator[] (int p);        // return the pth bird of the population
 
    // =======================================================================
    //                              Public Methods
    // =======================================================================
   	double _dt(void) const;

  	int _K(int i);                  //calculates the number of birds in the perception radius of the ith bird
	int _Kprim(int i);              //calculates the number of birds at the contact distance s, or closest, of the ith bird
  	int _O(int i);                  //calculates the number of obstacles at the contact distance s, or closest, of the ith bird
  	int _Opred(void); 				//calculates the number of obstacles at the contact distance s, or closest, of the ith bird
// Birds' speed	
	double v1x(int i);
	double v2x(int i);
	double v3x(int i);
	double v4x(int i);
	double windx(int i);
	double vx(int i);
	double v1y(int i);
	double v2y(int i);
	double v3y(int i);
	double v4y(int i);
	double windy(int i);
	double vy(int i);
	double xevol(int i);            // return the ith bird's x coordinate at t+dt time
	double yevol(int i);            // return the ith bird's y coordinate at t+dt time
// predator's speed
	Bird prey(void);         		// return the closest prey to the predator
	int preyindex(void);     		// return the closest prey's index
	double preyx(void);     		// return the coordinate x of the closest prey to the predator
	double preyy(void);	 			// return the coordinate y of the closest prey to the predator
	double vpredox(void);
	double vpredoy(void);
	double vpredx(void);
	double vpredy(void);
	double xpredevol(void);			// return the predator's x coordinate at t+dt time
	double ypredevol(void);			// return the predator's y coordinate at t+dt time


    // =======================================================================
    //                             Public Attributes
    // =======================================================================

  	static const double dt;                           // lapse of time
    
    static const int W;					// window's weight
	static const int H;					// window's height

	static const int N; 			// number of birds in the whole environment
	static const int P;             // number of obstacles
    Bird predator;									// predator

    static const double vpx;
    static const double vpy;



  protected :
	
    // =======================================================================
    //                             Protected Attributes
    // =======================================================================
    static const double r;                            // perception radius
    static const double c;                            // contact distance
    static const double Rp; 						// predator radius
    static const double m;							// prey catching distance for the predator
    Bird* population;                           // table of birds
    Obstacle* obstacles; 							// table of obstacles
 
 // parameters gamma1, gamma2 and gamma3  
	static const double gam1;
    static const double gam2;
    static const double gam3;
    static const double gam4;
};


// ===========================================================================
//                              Getters' definitions
// ===========================================================================

// ===========================================================================
//                              Setters' definitions
// ===========================================================================

// ===========================================================================
//                             Operators' definitions
// ===========================================================================



// ===========================================================================
//                          Inline functions' definition
// ===========================================================================



#endif


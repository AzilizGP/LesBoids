
#ifndef __BOID_H__
#define __BOID_H__


// ===========================================================================
//                                  Libraries
// ===========================================================================
#include <cstdio>
#include <cstdlib>
#include <ctime>

// ===========================================================================
//                                Project Files
// ===========================================================================
#include "Bird.h"
#include "Obstacle.h"

// ===========================================================================
//                              Class declarations
// ===========================================================================

class Boid
{
  public :
    
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

    int _N(void) const;					//total number of birds
    int _P(void) const;					// total number of ibstacles

	double _r(void) const;				// perception radius
	double _c(void) const;				// contact distance
	double _Rp(void) const;				// predator radius
	double _vpx(void) const;			// predator's speed when hunting
	double _vpy(void) const;			// predator's speed when hunting

	Bird* _population(void);
	Obstacle* _obstacles(void);
	Bird _predator(void);
	
// parameters' getters
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
   	void waiting(float temps);

	double distance(Bird b1, Bird b2);     // calculates the distance between 2 birds
	double distance(Bird b, Obstacle o);   // calculates the distance between a bird and an obstacle
  	int _K(int i);                  //calculates the number of birds in the perception radius of the ith bird
	int _Kprim(int i);              //calculates the number of birds at the contact distance s, or closest, of the ith bird
  	int _O(int i);                  //calculates the number of obstacles at the contact distance s, or closest, of the ith bird
  	int _Opred(void); 				//calculates the number of obstacles at the contact distance s, or closest, of the ith bird
  	
// Birds' speed	
	double v1x(int i);
	double v2x(int i);
	double v3x(int i);
	double v4x(int i);
	double vx(int i);
	
	double v1y(int i);
	double v2y(int i);
	double v3y(int i);
	double v4y(int i);
	double vy(int i);
	
	double xevol(int i);            // returns the ith bird's x coordinate at t+dt time
	double yevol(int i);            // returns the ith bird's y coordinate at t+dt time
	
// predator's speed
	Bird prey(void);         		// returns the closest prey to the predator
	int preyindex(void);     		// returns the closest prey's index
	double preyx(void);     		// returns the coordinate x of the closest prey to the predator
	double preyy(void);	 			// returns the coordinate y of the closest prey to the predator
	double vpredox(void);			// returns obstacles influence on the predator
	double vpredoy(void);
	double vpredx(void);			// returns the predator's speed
	double vpredy(void);
	
	double xpredevol(void);			// returns the predator's x coordinate at t+dt time
	double ypredevol(void);			// returns the predator's y coordinate at t+dt time


    // =======================================================================
    //                             Public Attributes
    // =======================================================================

  	static const double dt;         // lapse of time
    
    static const int W;				// window's weight
	static const int H;				// window's height

	static const int N; 			// number of birds in the whole environment
	static const int P;             // number of obstacles
    Bird predator;					// predator
    Bird* population;               // table of birds


    static const double vpx;		// predator's speed when hunting
    static const double vpy;



  protected :
	
    // =======================================================================
    //                             Protected Attributes
    // =======================================================================
    static const double r;          // perception radius
    static const double c;          // contact distance
    static const double Rp; 		// predator radius
    static const double m;			// prey catching distance for the predator
    Obstacle* obstacles; 			// table of obstacles
 
 // parameters gamma1, gamma2 and gamma3  
	static const double gam1;
    static const double gam2;
    static const double gam3;
    static const double gam4;
};


#endif


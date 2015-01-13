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


	Bird* _population(void);
	Obstacle* _obstacles(void);
	double _gam1(void) const;
	double _gam2(void) const;
	double _gam3(void) const;


    // =======================================================================
    //                            Accessors: setters
    // =======================================================================

    // =======================================================================
    //                                Operators
    // =======================================================================
	    
	Bird operator[] (int p);             // return the pth bird of the population
 
    // =======================================================================
    //                              Public Methods
    // =======================================================================
  	int _K(int i);                     //calculates the number of birds in the perception radius of the ith bird
	int _Kprim(int i);                     //calculates the number of birds at the contact distance s, or closest, of the ith bird
  	int _O(int i);                     //calculates the number of obstacles at the contact distance s, or closest, of the ith bird
	double v1x(int i);
	double v2x(int i);
	double v3x(int i);
	double vxevol(int i);
	double v1y(int i);
	double v2y(int i);
	double v3y(int i);
	double vyevol(int i);
		

    // =======================================================================
    //                             Public Attributes
    // =======================================================================
    
	static const int N; 			// number of birds in the whole environment
	static const int P;



  protected :
	
    // =======================================================================
    //                             Protected Attributes
    // =======================================================================
    static const double r;                            // perception radius
    static const double c;                            // contact distance

    Bird* population;                           // table of birds
    Obstacle* obstacles; 							// table of obstacles
 
 // parameters gamma1, gamma2 and gamma3  
	static const double gam1;
    static const double gam2;
    static const double gam3;

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


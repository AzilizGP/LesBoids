#ifndef __BIRD_H__
#define __BIRD_H__


// ===========================================================================
//                                  Libraries
// ===========================================================================
#include <cstdio>
#include <cstdlib>



// ===========================================================================
//                                Project Files
// ===========================================================================




// ===========================================================================
//                              Class declarations
// ===========================================================================

class Bird
{
  public :
    
    // =======================================================================
    //                                 Enums
    // =======================================================================
    
    // =======================================================================
    //                               Constructors
    // =======================================================================
    Bird(void);                            // constructor by default

    // =======================================================================
    //                                Destructor
    // =======================================================================
    ~Bird(void);

    // =======================================================================
    //                            Accessors: getters
    // =======================================================================

    int _K(void) const;
    int _x(void);
    int _y(void);
	int _vx(void);
	int _vy(void);
	int _dt(void) const;
	int _r(void) const;

	int _gam1(void) const;
	int _gam2(void) const;
	int _gam3(void) const;


    // =======================================================================
    //                            Accessors: setters
    // =======================================================================

    // =======================================================================
    //                                Operators
    // =======================================================================
	    
    // =======================================================================
    //                              Public Methods
    // =======================================================================
	int xmove(void);
	int ymove(void);
	int vxevol(void);
	int v1x(void);
	int v2x(void);
	int v3x(void);
	int vyevol(void);
	int v1y(void);
	int v2y(void);
	int v3y(void);
	

    // =======================================================================
    //                             Public Attributes
    // =======================================================================
    
	static const int K; // number of birds
	



  protected :

    // =======================================================================
    //                             Protected Attributes
    // =======================================================================
    int x;
    int y;
    int vx;
    int vy;
    static const int dt;
    static const int r;
 // parameters gamma1, gamma2 and gamma3  
	static const int gam1;
    static const int gam2;
    static const int gam3;

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



#endif // __STRING_H__

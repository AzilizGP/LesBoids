//****************************************************************************
//
//
//
//****************************************************************************


 
 
// ===========================================================================
//                                   Libraries
// ===========================================================================



// ===========================================================================
//                                 Project Files
// ===========================================================================
#include "Obstacle.h"
#include "cstdlib"
#include "ctime"



//############################################################################
//                                                                           #
//                              Class Obstacle                               #
//                                                                           #
//############################################################################

// ===========================================================================
//                         Definition of static attributes
// ===========================================================================

// ===========================================================================
//                                  Constructors
// ===========================================================================

Obstacle::Obstacle(void)
{
	x = (((double) rand())/RAND_MAX)*100;         //gives  a random number between 0 and 100
	y = (((double) rand())/RAND_MAX)*100;
}

Obstacle::Obstacle( const Obstacle& obstacle )
{
	// printf("call to Bird copy constructor\n");
	x = obstacle.x;
	y = obstacle.y;
}

// ===========================================================================
//                                  Destructor
// ===========================================================================
Obstacle::~Obstacle(void)
{
}

// ===========================================================================
//                                 Public Methods
// ===========================================================================

// ===========================================================================
//                                Protected Methods
// ===========================================================================

// ===========================================================================
//                               Non inline accessors
// ===========================================================================


double Obstacle::_x()
{
  return x;
}
//--------------------------------------------------------------------------
double Obstacle::_y()
{
  return y;
}
//****************************************************************************
// implémenter v3v et v3y
// les obstacles
// 
//
//****************************************************************************


 
 
// ===========================================================================
//                                   Libraries
// ===========================================================================



// ===========================================================================
//                                 Project Files
// ===========================================================================
#include <cstdio>
#include <cstdlib>
#include "Boid.h"
#include "Bird.h"
#include <cmath>



//############################################################################
//                                                                           #
//                              Class Bird                                   #
//                                                                           #
//############################################################################

// ===========================================================================
//                         Definition of static attributes
// ===========================================================================

 const int Boid::N=100;
 const double Boid::r=20;
 const double Boid::c=10;

 const double Boid::gam1=1;
 const double Boid::gam2=1;
 const double Boid::gam3=1;

// ===========================================================================
//                                  Constructors
// ===========================================================================
Boid::Boid(void)                      // create a population of N birds  in a table
{
	population = new Bird[N]; 	
}

Boid::Boid( const Boid& boid )
{
	printf("ERREUR\n");
	exit(1);
}

// ===========================================================================
//                                  Destructor
// ===========================================================================
Boid::~Boid(void)
{
	delete [] population;
}
// =======================================================================
//                                Operators
// =======================================================================


Bird Boid::operator[](int p)              // return the pth bird of the population
{
	if(p<0 || p>N-1)
	{
      printf("out of range, you've tried with %d, please try again with a number between 0 and length = %d \n",p,N-1);
	  exit(EXIT_FAILURE);
	}
	return this->population[p];
}



// ===========================================================================
//                                 Public Methods
// ===========================================================================

double distance(Bird bird1, Bird bird2)      // calculates the distance between 2 birds
{
	double x1 = bird1._x();
	double y1 = bird1._y();
	double x2 = bird2._x();
	double y2 = bird2._y();
	double dist;
	dist = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
	return dist;
}

 //--------------------------------------------------------------------------

int Boid::_K(int i)                     //calculates the number of birds in the perception radius of the ith bird
{
	if(i<0||i>N-1)
	{
	printf("Warning : your index number must be between 0 and <%d\n",(N-1));
    exit(EXIT_FAILURE);
	}
	int j;
	int p=0;
	for (j=0;j<(N-1);j++)
	{
		Bird* b;
		b=this->population;
		Bird b1, b2;
		b1=b[i];
		b2=b[j];
		if( distance(b1,b2) < r )
		{
			p=p+1;
		};
	};
	return p;
}

//--------------------------------------------------------------------------

 double Boid::v1x(int i)
{
	int j;
	int K=0;
	int v1x;
	int v1xi= this->population[i]._vx();
	int v1xj;
	for (j=0 ; j<N && j!=i && distance(this->population[i],this->population[j]) ; j++)
	{
		v1xj= this->population[j]._vx();
		v1x += v1xj - v1xi;
		K++;
	}
	v1x = v1x / K ;
	return v1x;
}
//--------------------------------------------------------------------------

 double Boid::v1y(int i)
{
	int j;
	int K=0;
	int v1y;
	int v1yi= this->population[i]._vy();
	int v1yj;
	for (j=0 ; j<N && j!=i && distance(this->population[i],this->population[j]); j++)
	{
		v1yj= this->population[j]._vy();
		v1y += v1yj - v1yi;
		K++;
	}
	v1y = v1y / K;
	return v1y;
}

//--------------------------------------------------------------------------
 double Boid::v2x(int i)
{
	int j;
	int K=0;
	int v2x;
	int xi= this->population[i]._x();
	int xj;
	for (j=0 ; j<N && j!=i && distance(this->population[i],this->population[j]) ; j++)
	{
		xj= this->population[j]._x();
		v2x += xj - xi;
		K++;
	}
	v2x = v2x / K;
	return v2x;
}
//--------------------------------------------------------------------------
 double Boid::v2y(int i)
{
	int j;
	int K=0;
	int v2y;
	int yi= this->population[i]._y();
	int yj;
	for (j=0 ; j<N && j!=i && distance(this->population[i],this->population[j]) ; j++)
	{
		yj= this->population[j]._y();
		v2y += yj - yi;
		K++;
	}
	v2y = v2y / K;
	return v2y;
}
//--------------------------------------------------------------------------
 double Boid::v3x(int i)
 {
	 
 }
//--------------------------------------------------------------------------
 double Boid::v3y(int i)
 {
	 
 }

//--------------------------------------------------------------------------
/*
double Boid::vxevol(void)
{
	return vx + dt*(gam1*v1x + gam2*v2x + gam3*v3x);
}
*/
//--------------------------------------------------------------------------
/*
double Boid::vyevol(void)
{
	return vy + dt*(gam1*v1y + gam2*v2y + gam3*v3y);
}
*/
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------

//--------------------------------------------------------------------------

//--------------------------------------------------------------------------

// ===========================================================================
//                                Protected Methods
// ===========================================================================

// ===========================================================================
//                               Non inline accessors
// ===========================================================================

int Boid::_N() const
{
	return N;
}
//--------------------------------------------------------------------------
double Boid::_r() const
{
  return r;
}
//--------------------------------------------------------------------------
double Boid::_c() const
{
  return c;
}
//--------------------------------------------------------------------------
Bird* Boid::_population() 
{
  return population;
}
//--------------------------------------------------------------------------
double Boid::_gam1() const
{
	return gam1;
}
//--------------------------------------------------------------------------
double Boid::_gam2() const
{
	return gam2;
}
//--------------------------------------------------------------------------
double Boid::_gam3() const
{
	return gam3;
}

//****************************************************************************
// implémenter v3v et v3y
// les obstacles
// K' -> idem que pour K, s'implémente dans v3
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
#include "Obstacle.h"
#include <cmath>



//############################################################################
//                                                                           #
//                              Class Bird                                   #
//                                                                           #
//############################################################################

// ===========================================================================
//                         Definition of static attributes
// ===========================================================================

 const int Boid::N=100;					// number of birds
 const int Boid::P=10;					// number of obstacles
 const double Boid::r=20;				// perception radius
 const double Boid::c=10;				// contact distance

 const double Boid::gam1=1;
 const double Boid::gam2=1;
 const double Boid::gam3=1;

// ===========================================================================
//                                  Constructors
// ===========================================================================
Boid::Boid(void)                      // create a population of N birds  in a table
{
	population = new Bird[N];
	obstacles = new Obstacle[P]; 	
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
double distance(Obstacle obs1, Obstacle obs2)      // calculates the distance between 2 obstacles
{
	double x1 = obs1._x();
	double y1 = obs1._y();
	double x2 = obs2._x();
	double y2 = obs2._y();
	double dist;
	dist = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
	return dist;
}
//--------------------------------------------------------------------------

int Boid::_K(int i)                     //calculates the number of birds in the perception radius r of the ith bird
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

int Boid::_Kprim(int i)                     //calculates the number of birds at the contact distance c, or closest, of the ith bird
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
		if( distance(b1,b2) < c )
		{
			p=p+1;
		};
	};
	return p;
}
//--------------------------------------------------------------------------

int Boid::_O(int i)                     //calculates the number of obstacles at the contact distance c, or closest, of the ith bird
{
	if(i<0||i>N-1)
	{
	printf("Warning : your index number must be between 0 and <%d\n",(P-1));
    exit(EXIT_FAILURE);
	}
	int j;
	int p=0;
	for (j=0;j<(N-1);j++)
	{
		Obstacle* obs;
		obs=this->obstacles;
		Obstacle b1, b2;
		b1=obs[i];
		b2=obs[j];
		if( distance(b1,b2) < c )
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
	int K=this->_K(i);
	double v1x=0;
	if(K!=0)
	{
		double xi=this->population[i]._x();
		double xj;
		for (j=0 ; j<N ; j++)
			{
				if(j!=i && distance(this->population[i],this->population[j])<r)
				{
					xj = this->population[j]._vx();
					v1x += xj - xi;
				}
			}
		v1x = v1x / K ;
	}
	return v1x;
}
//--------------------------------------------------------------------------

 double Boid::v1y(int i)
{
	int j;
	int K=this->_K(i);
	double v1y=0;
	if(K!=0)
	{
		double v1yi= this->population[i]._vy();
		double v1yj;
		for (j=0 ; j<N ; j++)
		{
			if(j!=i && distance(this->population[i],this->population[j])<r)
			{
				v1yj= this->population[j]._vy();
				v1y += v1yj - v1yi;
			}
		}
		v1y = v1y / K;
	}
	return v1y;
}

//--------------------------------------------------------------------------
 double Boid::v2x(int i)
{
	int j;
	int K=this->_K(i);
	double v2x=0;
	if(K!=0)
	{
		double xi= this->population[i]._x();
		double xj;
		for (j=0 ; j<N ; j++)
		{
			if(j!=i && distance(this->population[i],this->population[j])<r)
			{
				xj= this->population[j]._x();
				v2x += xj - xi;
			}
		}
		v2x = v2x / K;
	}
	return v2x;
}
//--------------------------------------------------------------------------

 double Boid::v2y(int i)
{
	int j;
	int K=this->_K(i);
	double v2y=0;
	if(K!=0)
	{
		double yi= this->population[i]._y();
		double yj;
		for (j=0 ; j<N ; j++)
		{
			if(j!=i && distance(this->population[i],this->population[j])<r)
			{
				yj= this->population[j]._y();
				v2y += yj - yi;
			}
		}
			v2y = v2y / K;
	}
	return v2y;
}

//--------------------------------------------------------------------------
 double Boid::v3x(int i)
 {
	double v3x;
	int j;
	
	int Kprim=this->_Kprim(i);
	double vbx=0;
	if(Kprim!=0)
	{
		double xi= this->population[i]._x();
		double xj;
		for (j=0 ; j<N ; j++)
		{
			if(j!=i && distance(this->population[i],this->population[j])<c)
			{
				xj= this->population[j]._x();
				vbx += xj - xi;
				Kprim++;
			}
		}
			vbx = vbx / Kprim;
	}
	
	int O=this->_O(i);
	double vox=0;
	if(O!=0)
	{
		double xi= this->obstacles[i]._x();
		double xj;
		for (j=0 ; j<P ; j++)
		{
			if(j!=i && distance(this->obstacles[i],this->obstacles[j])<c)
			{
				xj= this->obstacles[j]._x();
				vox += xj - xi;
				O++;
			}
		}
			vox = vox / O;
	}
	v3x = -vox - vbx;
	return v3x;
 }
//--------------------------------------------------------------------------
 double Boid::v3y(int i)
 {
	double v3y;
	int j;
	
	int Kprim=this->_Kprim(i);
	double vby=0;
	if(Kprim!=0)
	{
		double yi= this->population[i]._y();
		double yj;
		for (j=0 ; j<N ; j++)
		{
			if(j!=i && distance(this->population[i],this->population[j])<c)
			{
				yj= this->population[j]._y();
				vby += yj - yi;
				Kprim++;
			}
		}
			vby = vby / Kprim;
	}
	
	int O=this->_O(i);
	double voy=0;
	if(O!=0)
	{
		double yi= this->obstacles[i]._y();
		double yj;
		for (j=0 ; j<P ; j++)
		{
			if(j!=i && distance(this->obstacles[i],this->obstacles[j])<c)
			{
				yj= this->obstacles[j]._y();
				voy += yj - yi;
				O++;
			}
		}
			voy = voy / O;
	}
	v3y = - voy - vby;
	return v3y;
 }

//--------------------------------------------------------------------------

double Boid::vxevol(int i)
{
	return this->population[i]._vx() + this->population[i]._dt() * (gam1*(this->v1x(i)) + gam2*(this->v2x(i)) + gam3*(this->v3x(i)));
}

//--------------------------------------------------------------------------

double Boid::vyevol(int i)
{
	return this->population[i]._vy() + this->population[i]._dt() * (gam1*this->v1y(i) + gam2*this->v2y(i) + gam3*this->v3y(i));
}
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
int Boid::_P() const
{
	return P;
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
Obstacle* Boid::_obstacles() 
{
  return obstacles;
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

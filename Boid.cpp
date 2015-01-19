//****************************************************************************
// vent
// verifier les vitesses d'obstacles
// supprimer l'oiseau manger, arrêter le prédateur quand il mange
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


 const int Boid::W=800;					// window's weight
 const int Boid::H=800;					// window's height 

 const int Boid::N=100;					// number of birds
 const int Boid::P=5;					// number of obstacles
 const double Boid::r=100;				// perception radius
 const double Boid::c=10;				// contact distance
 const double Boid::Rp=100;				// predator radius
 const double Boid::m=20;				// prey catching distance for the predator
 const double Boid::vpx=10;
 const double Boid::vpy=10;

 const double Boid::gam1=0.5;
 const double Boid::gam2=0.2;
 const double Boid::gam3=1;
 const double Boid::gam4=5;

// ===========================================================================
//                                  Constructors
// ===========================================================================
Boid::Boid(void)                      // create a population of N birds  in a table
{
	population = new Bird[N];
	obstacles = new Obstacle[P];
	Bird predator; 	
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
      printf("out of range, you've tried with %d, please try again with a number between 0 and length = %d to obtain the bird you want in the boid's population\n",p,N-1);
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
double distance(Bird b, Obstacle o)      // calculates the distance between a bird and an obstacle
{
	double xb = b._x();
	double yb = b._y();
	double xo = o._x();
	double yo = o._y();
	double dist;
	dist = sqrt( (xb-xo)*(xb-xo) + (yb-yo)*(yb-yo) );
	return dist;
}
//--------------------------------------------------------------------------

int Boid::_K(int i)                     //calculates the number of birds in the perception radius r of the ith bird
{
	if(i<0||i>N-1)
	{
	printf("Warning : your index number must be between 0 and <%d to obtain the K you wanted\n",(N-1));
    exit(EXIT_FAILURE);
	}
	int j;
	int p=0;
	for (j=0;j<this->N;j++)
	{
		Bird b1, b2;
		b1=this->population[i];
		b2=this->population[j];
		if( j!=i && distance(b1,b2) < r )
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
	printf("Warning : your index number must be between 0 and <%d to obtain the Kprim you wanted\n",(N-1));
    exit(EXIT_FAILURE);
	}
	int j;
	int p=0;
	for (j=0;j<this->N;j++)
	{
		Bird b1, b2;
		b1=this->population[i];
		b2=this->population[j];
		if( j!=i && distance(b1,b2) < c )
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
	printf("Warning : your index number must be between 0 and <%d to obtain the number of obstacles\n",(P-1));
    exit(EXIT_FAILURE);
	}
	int j;
	int p=0;
	Bird b = this->population[i];       // b is the bird concerned
	for (j=0;j<this->P;j++)
	{
		Obstacle obs = this->obstacles[j];
		if( distance(b,obs) < c )
		{
			p=p+1;
		};
	};
	return p;
}
//--------------------------------------------------------------------------

int Boid::_Opred(void)                     //calculates the number of obstacles at the contact distance c, or closest, of the predator
{
	int j;
	int p=0;
	for (j=0;j<this->P;j++)
	{
		Obstacle obs = this->obstacles[j];
		if( distance(this->predator,obs) < c )
		{
			p=p+1;
		};
	};
	return p;
}
//--------------------------------------------------------------------------

 double Boid::v1x(int i)            // v1x
{
	int j;
	int K=this->_K(i);
	double v1x=0;
	if(K!=0)
	{
		double vxi=this->population[i]._vx();
		double vxj;
		for (j=0 ; j<this->N ; j++)
			{
				if(j!=i && distance(this->population[i],this->population[j])<r)
				{
					vxj = this->population[j]._vx();
					v1x += vxj - vxi;
				}
			}
		v1x = v1x / K ;
	}
	return v1x;
}
//--------------------------------------------------------------------------

 double Boid::v1y(int i)            //v1y
{
	int j;
	int K=this->_K(i);
	double v1y=0;
	if(K!=0)
	{
		double v1yi= this->population[i]._vy();
		double v1yj;
		for (j=0 ; j<this->N ; j++)
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
 double Boid::v2x(int i)                //v2x
{
	int j;
	int K=this->_K(i);
	double v2x=0;
	if(K!=0)
	{
		double xi= this->population[i]._x();
		double xj;
		for (j=0 ; j<this->N ; j++)
		{
			if((j!=i) && (distance(this->population[i],this->population[j])<r))
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

 double Boid::v2y(int i)                    // v2y
{
	int j;
	int K=this->_K(i);
	double v2y=0;
	if(K!=0)
	{
		double yi= this->population[i]._y();
		double yj;
		for (j=0 ; j<this->N ; j++)
		{
			if((j!=i) && (distance(this->population[i],this->population[j])<r))
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
 double Boid::v3x(int i)                       //v3x
 {
	double v3x=0;
	int j;
	
	int Kprim=this->_Kprim(i);
	double vbx=0;
	if(Kprim!=0)
	{
		double xi= this->population[i]._x();
		double xj;
		for (j=0 ; j<this->N ; j++)
		{
			if(j!=i && distance(this->population[i],this->population[j])<c)
			{
				xj= this->population[j]._x();
				vbx += xj - xi;
			}
		}
		vbx = vbx / Kprim;
	}
	
	int O=this->_O(i);
	double vox=0;
	if(O!=0)
	{

		double xi= this->population[i]._x();
		double xj;
		for (j=0 ; j<this->P ; j++)
		{
			if(j!=i && distance(this->population[i],this->obstacles[j])<c)
			{
				xj= this->obstacles[j]._x();
				vox += xj - xi;
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
	double v3y=0;
	int j;
	
	int Kprim=this->_Kprim(i);
	double vby=0;
	if(Kprim!=0)
	{
		double yi= this->population[i]._y();
		double yj;
		for (j=0 ; j<this->N ; j++)
		{
			if(j!=i && distance(this->population[i],this->population[j])<c)
			{
				yj= this->population[j]._y();
				vby += yj - yi;
			}
		}
		vby = vby / Kprim;
	}
	
	int O=this->_O(i);
	double voy=0;
	if(O!=0)
	{
		double yi= this->population[i]._y();
		double yj;
		for (j=0 ; j<this->P ; j++)
		{
			if(j!=i && distance(this->population[i],this->obstacles[j])<c)
			{
				yj= this->obstacles[j]._y();
				voy += yj - yi;
			}
		}
		voy = voy / O;
	}
	v3y = - voy - vby;
	return v3y;
 }
//--------------------------------------------------------------------------
 Bird Boid::prey(void)          // return the closest prey 
{
	int x=100000;                // x = smallest distance prey-predator
	int u;
	int m;						// l = index of the closest prey to the predator
	int k;
	for(k=0; k< this->N; k++)
	{
		u = distance(this->population[k],this->predator);
		if( u < x )
		{
			x = u;
			m=k;
		}
	}
	return this->population[m];	
}
//--------------------------------------------------------------------------
 int Boid::preyindex(void)            // return the index of the closest prey
{
	int x=100000;                // x = smallest distance prey-predator
	int u;
	int m;						// l = index of the closest prey to the predator
	int k;
	for(k=0; k< this->N; k++)
	{
		u = distance(this->population[k],this->predator);
		if(u < x )
		{
			x = u;
			m=k;
		}
	}
	return m;	
}
//--------------------------------------------------------------------------
double Boid::preyx(void)            // return the prey's coordinate x
{
	return this->prey()._x();
}
//--------------------------------------------------------------------------
double Boid::preyy(void)            // return the prey's coordinate y
{
	return this->prey()._y();
}
//--------------------------------------------------------------------------
double Boid::v4x(int i)                 // v4x
{
	double xpred = this->predator._x();
	double xprey = this->population[i]._x();
	return -(xpred - xprey) / distance(this->predator , this->population[i]);
}
//--------------------------------------------------------------------------
double Boid::v4y(int i)                    //v4y
{
	double ypred = this->predator._y();
	double yprey = this->population[i]._y();
	return -(ypred - yprey) / distance(this->predator , this->population[i]);
}

//--------------------------------------------------------------------------
double Boid::vx(int i)                        //vx
{
	return this->population[i]._vx() + this->population[i]._dt() * (gam1*this->v1x(i) + gam2*this->v2x(i) + gam3*this->v3x(i) + gam4*this->v4x(i));
}
//--------------------------------------------------------------------------

double Boid::vy(int i)                        //vy 
{
	return this->population[i]._vy() + this->population[i]._dt() * (gam1*this->v1y(i) + gam2*this->v2y(i) + gam3*this->v3y(i) + gam4*this->v4y(i));
}
//--------------------------------------------------------------------------
 double Boid::vpredox(void)                   //vpredox (obstacles influence on the predator)
 {
	int j;
	int O=this->_Opred();
	double vox=0;
	if(O!=0)
	{
		double xj;
		for (j=0 ; j<this->P ; j++)
		{
			if(distance(this->predator,this->obstacles[j])<c)
			{
				xj= this->obstacles[j]._x();
				vox += xj - this->predator._x();
			}
		}
			vox = vox / O;
	}
	return vox;
 }
//--------------------------------------------------------------------------
 double Boid::vpredoy(void)                        // vpredoy (obstacles influence on the predator)
 {	
	int j;
	int O=this->_Opred();
	double voy=0;
	if(O!=0)
	{
		for (j=0 ; j<this->P ; j++)
		{
			if(distance(this->predator,this->obstacles[j])<c)
			{
				voy += this->obstacles[j]._y() - this->predator._y();
			}
		}
			voy = voy / O;
	}
	return voy;
 }
//--------------------------------------------------------------------------
double Boid::vpredx(void)
{
	double vpredx;
	if(distance(this->predator , this->prey()) > Rp)
	{
		vpredx=(((double) rand())/RAND_MAX);
		if(distance(this->predator, this->prey())<m)
		{
			vpredx=0;
		}
	}
	else
	{
		vpredx =  vpx * v4x(this->preyindex());
	}
	return vpredx - this->vpredox();
}
//--------------------------------------------------------------------------

double Boid::vpredy(void)
{
	double vpredy;
	if(distance(this->predator , this->prey()) > Rp)
	{
		vpredy=(((double) rand())/RAND_MAX);
		if(distance(this->predator, this->prey())<m)
		{
			vpredy=0;
		}
	}
	else
	{
		vpredy =  vpy * v4y(this->preyindex());
	}
	return vpredy - this->vpredoy();
}

//--------------------------------------------------------------------------
double Boid::xevol(int i)              // x(t+dt)
{
	return (this->population[i].dt * this->vx(i));
}

//--------------------------------------------------------------------------
double Boid::yevol(int i)             // y(t+dt)
{
	return (this->population[i].dt * this->vy(i));
}
//--------------------------------------------------------------------------
double Boid::xpredevol(void)
{
	return this->predator._x() + this->predator.dt * this->vpredx();
}
//--------------------------------------------------------------------------
double Boid::ypredevol(void)
{
	return this->predator._y() + this->predator.dt * this->vpredy();
}

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
double Boid::_Rp() const
{
  return Rp;
}
//--------------------------------------------------------------------------
double Boid::_vpx() const
{
  return vpx;
}
//--------------------------------------------------------------------------
double Boid::_vpy() const
{
  return vpy;
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
Bird Boid::_predator() 
{
  return predator;
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
//--------------------------------------------------------------------------
double Boid::_gam4() const
{
	return gam4;
}

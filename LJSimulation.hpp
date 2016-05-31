#ifndef _LJSIMULATION_HPP
#define _LJSIMULATION_HPP

#include <random>
#include <map>
#include <iomanip>
#include "Particle.hpp"

class LJSimulation 
{
public:
  LJSimulation();
  
  void init(int Npart);
  void start();
private:
  Particle *particles;

  int _npart;			//number of particles
  real_type _rho;		//density of the system
  real_type _dt;		//time step of the simulation
  real_type _rc;		//cutoff radius
  int	_nsteps;		//number of simulation steps
  real_type _T0;		//initial temperature of the system
  int	_sf;			//sample frequency
};

#endif
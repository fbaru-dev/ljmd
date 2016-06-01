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
  ~LJSimulation();
  
  void init();
  void set_number_of_particles(int N);
  void start(int nsteps);
  
private:
  Particle *particles;
  
  int _npart;			//number of particles
  real_type _density;		//density of the system
  real_type _tstep;		//time step of the simulation
  real_type _rcut;		//cutoff radius
  int	_nsteps;		//number of integration steps
  real_type _Tinit;		//initial temperature of the system
  int	_sfreq;			//sample frequency
  
  int	_n3;			//number of particle for each side of the box 
  real_type _sideLength;	//side length of the simulation box
  
  void init_parameters();	//initialization of the simulation parameters
  void init_compute();		//compute the initial parameters setup
  
  void init_positions();	//TODO: initialization from a file
  void init_velocities();
  void init_forces() {};	
  
  inline void set_npart(const int &N){ _npart = N; }
  inline int get_npart() const {return _npart; }
  
  inline void set_density(const real_type &rho){ _density = rho; }
  inline real_type get_density() const {return _density; }
  
  inline void set_tstep(const real_type &dt){ _tstep = dt; }
  inline real_type get_tstep() const {return _tstep; }
  
  inline void set_rcut(const real_type &rc){ _rcut = rc; }
  inline real_type get_rcut() const {return _rcut; }
  
  inline void set_nsteps(const int &n){ _nsteps = n; }
  inline int get_nsteps() const {return _nsteps; }
  
  inline void set_Tinit(const real_type &T){ _Tinit = T; }
  inline real_type get_Tinit() const {return _Tinit; }
  
  inline void set_sfreq(const int &sf){ _sfreq = sf; }
  inline int get_sfreq() const {return _sfreq; }
  
  inline void set_n3(const int &n){ _n3 = n; }
  inline int get_n3() const {return _n3; }
  
  inline void set_sideLength(const real_type &L){ _sideLength = L; }
  inline real_type get_sideLength() const {return _sideLength; }
  
};

#endif
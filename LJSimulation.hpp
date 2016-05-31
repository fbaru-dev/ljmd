#ifndef _LJSIMULATION_HPP
#define _LJSIMULATION_HPP

#include "Particle.hpp"

class LJSimulation 
{
public:
  LJSimulation();
  
  void init(int Npart);
  void start();
private:
  int _Npart;
  Particle *particles;
};

#endif
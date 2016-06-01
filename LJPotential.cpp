#include "LJPotential.hpp"

LJPotential :: LJPotential() : _epsilon(1.0), _sigma(1.0)
{
  set_shift(0.0);	
  set_cutoff(1.0);
  preset();
}

LJPotential :: LJPotential(real_type epsilon, real_type sigma) : _epsilon(epsilon), _sigma(sigma)
{
  set_shift(0.0);	
  set_cutoff(1.0);
  preset();
}

LJPotential :: LJPotential(real_type epsilon, real_type sigma, real_type cutoff, real_type shift)
{
  set_epsilon(epsilon);
  set_sigma(sigma);
  set_shift(shift);	
  set_cutoff(cutoff);
  preset();
}

void LJPotential :: preset()
{
  real_type sigma2 = get_sigma() * get_sigma();
  real_type sigma6 = sigma2 * sigma2 * sigma2;
  forcef1 = 48.0 * get_epsilon() * sigma6 * sigma6;
  forcef2 = 24.0 * get_epsilon() * sigma6;
  energyf1 = 4.0 * get_epsilon() * sigma6 * sigma6;
  energyf2 = 4.0 * get_epsilon() * sigma6;
}

real_type LJPotential :: compute_force(real_type distance2)
{
  real_type idistance6 = 1.0 / (distance2 * distance2 * distance2);
  real_type f1 = forcef1 * idistance6 * idistance6;
  real_type f2 = forcef2 * idistance6;
  
  return  f1 - f2;
}

real_type LJPotential :: compute_energy(real_type distance2) 
{
  real_type idistance6 = 1.0 / (distance2 * distance2 * distance2);
  real_type e1 = energyf1 * idistance6 * idistance6;
  real_type e2 = energyf2 * idistance6;
    
  return e1 - e2;
}
#ifndef _LJPOTENTIAL_HPP
#define _LJPOTENTIAL_HPP

#include "Vec3D.hpp"

class LJPotential 
{
private:
  real_type _epsilon;
  real_type _sigma;
  real_type _shift;		//not yet used
  real_type _cutoff;		//not yet used
  
  real_type forcef1, forcef2;	//force factor for the LJ potential
  real_type energyf1, energyf2; //energy factor for the LJ potential 	
  
  void preset();
public:
  LJPotential(); 
  LJPotential(real_type epsilon, real_type sigma);
  LJPotential(real_type epsilon, real_type sigma, real_type cutoff, real_type shift);
  
 // Setter and getter
  void set_epsilon(real_type epsilon) { _epsilon = epsilon; preset(); }
  real_type get_epsilon() const { return _epsilon; }

  void set_sigma(real_type sigma) { _sigma = sigma; preset(); }
  real_type get_sigma() const { return _sigma; }
  
  void set_shift(real_type shift) { _shift = shift; preset(); }
  real_type get_shift() const { return _shift; }

  void set_cutoff(real_type cutoff) { _cutoff = cutoff; preset(); }
  real_type get_cutoff() const { return _cutoff; }
  
  real_type compute_force(real_type distance2);
  real_type compute_energy(real_type distance2);
};  

#endif
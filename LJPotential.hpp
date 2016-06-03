#ifndef _LJPOTENTIAL_HPP
#define _LJPOTENTIAL_HPP

#include "Vec3D.hpp"

class LJPotential 
{
private:
  real_type _epsilon;
  real_type _sigma;
  
  real_type forcef1, forcef2;	//force factor for the LJ potential
  real_type energyf1, energyf2; //energy factor for the LJ potential 	
  
  //sLRC Standard Long Range Correction factors
  real_type presscorrf1, presscorrf2;	   //correction to the pressure formulas
  real_type energycorrf1, energycorrf2;	   //correction to the energy (potential)
  
  void preset();
public:
  LJPotential(); 
  LJPotential(real_type epsilon, real_type sigma);
  
 // Setter and getter
  void set_epsilon(real_type epsilon) { _epsilon = epsilon; preset(); }
  real_type get_epsilon() const { return _epsilon; }

  void set_sigma(real_type sigma) { _sigma = sigma; preset(); }
  real_type get_sigma() const { return _sigma; }
  
  real_type compute_force(real_type distance2);
  real_type compute_energy(real_type distance2);
  
  real_type compute_p_corr(real_type rcut, real_type rho);
  real_type compute_e_corr(real_type rcut, real_type rho);	
};  

#endif
/*
    This file is part of the program ljmd, a Lennard Jones Molecular
    Dynamics code written for teaching and testing functionalities.
    
    Copyright (C) 2016  Fabio Baruffa <fbaru-dev@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
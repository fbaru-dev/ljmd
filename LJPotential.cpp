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

#include "LJPotential.hpp"

LJPotential :: LJPotential() : _epsilon(1.0), _sigma(1.0)
{
  preset();
}

LJPotential :: LJPotential(real_type epsilon, real_type sigma) : _epsilon(epsilon), _sigma(sigma)
{
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
  
  presscorrf1  = 32.0/9.0 * M_PI * get_epsilon() * sigma6 * sigma6;
  presscorrf2  = 16.0/3.0 * M_PI * get_epsilon() * sigma6;
  energycorrf1 = 8.0/9.0  * M_PI * get_epsilon() * sigma6 * sigma6;
  energycorrf2 = 8.0/3.0  * M_PI * get_epsilon() * sigma6;
}

real_type LJPotential :: compute_force(real_type distance2)			//tot:7flops
{
  real_type idistance6 = 1.0 / (distance2 * distance2 * distance2);		//1div + 2mul = 3flops	
  real_type f1 = forcef1 * idistance6 * idistance6;				//2flops
  real_type f2 = forcef2 * idistance6;						//1flop
  
  return  f1 - f2;								//1flop
}

real_type LJPotential :: compute_energy(real_type distance2) 			//tot:7flops
{
  real_type idistance6 = 1.0 / (distance2 * distance2 * distance2);		//1div + 2mul = 3flops
  real_type e1 = energyf1 * idistance6 * idistance6;				//2flops
  real_type e2 = energyf2 * idistance6;						//1flop
    
  return e1 - e2;								//1flop
}

real_type LJPotential :: compute_p_corr(real_type rcut, real_type rho) 
{
  real_type rrcut3 = 1.0/(rcut*rcut*rcut);
  real_type rrcut9 = rrcut3*rrcut3*rrcut3;
  return (presscorrf1*rho*rho*rrcut9 - presscorrf2*rho*rho*rrcut3);
}

real_type LJPotential :: compute_e_corr(real_type rcut, real_type rho) 
{
  real_type rrcut3 = 1.0/(rcut*rcut*rcut);
  real_type rrcut9 = rrcut3*rrcut3*rrcut3;
  return (energycorrf1*rho*rrcut9 - energycorrf2*rho*rrcut3);
}
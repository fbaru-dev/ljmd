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

#include <iostream>

#include "LJSimulation.hpp"

//TODO: write a useful user friendly interface
int main(int argc, char** argv) 
{
  int N;	//number of particles
  int nstep; 	//number ot integration steps
  LJSimulation sim;
  
  sim.init();
  
  if(argc>1)
  {
    N=atoi(argv[1]);
    sim.set_number_of_particles(N);  
    if(argc==3) 
    {
      nstep=atoi(argv[2]);
      sim.set_number_of_steps(nstep);  
    }
  }
  
  sim.start();

  return 0;
}
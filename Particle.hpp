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

#ifndef _PARTICLE_HPP
#define _PARTICLE_HPP

#include "Vec3D.hpp"

struct Particle
{
  private:
    Vec3D<real_type> position;
    Vec3D<real_type> velocity;
    Vec3D<real_type> force;
  public:
    Particle() { init();}
    void init() 
    {
      position;
      velocity;
      force;
    }
    
    Vec3D<real_type>& pos() { return position; }
    const Vec3D<real_type>& pos() const { return position; }
    Vec3D<real_type> getPos() const { return position; }
    void setPos(const Vec3D<real_type> &pos) { position = pos; }
    
    Vec3D<real_type>& vel() { return velocity; }
    const Vec3D<real_type>& vel() const { return velocity; }
    Vec3D<real_type> getVel() const { return velocity; }
    void setVel(const Vec3D<real_type> &vel) { velocity = vel; }
    
    Vec3D<real_type>& f() { return force; }
    const Vec3D<real_type>& f() const { return force; }
    Vec3D<real_type> getF() const { return force; }
    void setF(const Vec3D<real_type> &f) { force = f; } 
    
};

#endif
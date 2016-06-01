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
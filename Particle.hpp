#ifndef _PARTICLE_HPP
#define _PARTICLE_HPP

#include "Vec3D.hpp"
typedef double real_type;

struct Particle
{
  private:
    Vec3D<real_type> position;
    Vec3D<real_type> velocity;
    Vec3D<real_type> force;
    Vec3D<int> bound;
  public:
    Particle() { init();}
    void init() 
    {
      position;
      velocity;
      force;
      bound;
    }
    // getter and setter 
    
    Vec3D<real_type> getPos() const { return position; }
    void setPos(const Vec3D<real_type> &pos) { position = pos; }
    
    Vec3D<real_type> getVel() const { return velocity; }
    void setVel(const Vec3D<real_type> &vel) { velocity = vel; }
    
    Vec3D<real_type> getF() const { return force; }
    void setF(const Vec3D<real_type> &f) { force = f; }
    
    Vec3D<int> getBound() const { return bound; }
    void setBound(const Vec3D<int> &b) { bound = b; }
    
};

#endif
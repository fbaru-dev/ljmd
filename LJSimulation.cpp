#include "LJSimulation.hpp"

LJSimulation :: LJSimulation()
{
  cout << "Start Sumlation!" << endl;
}

void LJSimulation :: init(int Npart)  
{
  _Npart = Npart;
  particles = new Particle[Npart];
  
  cout << "Start Simulation with " << _Npart << " particles!" << endl;
  
  for(int i=0; i<Npart; ++i) particles[i].init();
  for(int i=0; i<Npart; ++i) particles[i].setPos(1.1);
  for(int i=0; i<Npart; ++i) particles[i].setVel(2.2);
  for(int i=0; i<Npart; ++i) particles[i].setF(3.3);  
  for(int i=0; i<Npart; ++i) particles[i].setBound(4);  
  
  for(int i=0; i<Npart; ++i) cout << particles[i].getPos() << endl;
  for(int i=0; i<Npart; ++i) cout << particles[i].getVel() << endl;
  for(int i=0; i<Npart; ++i) cout << particles[i].getF() << endl;  
  for(int i=0; i<Npart; ++i) cout << particles[i].getBound() << endl;  
  
  delete particles;
}

void LJSimulation :: start() {cout << "START" << endl;}
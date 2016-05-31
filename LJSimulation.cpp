#include "LJSimulation.hpp"

LJSimulation :: LJSimulation()
{
  std::cout << "Start Sumlation!" << std::endl;
}

void LJSimulation :: init(int Npart)  
{
  _npart = Npart;
  particles = new Particle[Npart];
  
  std::random_device rd;	//random number generator	
  std::mt19937 gen(rd());      
  std::exponential_distribution<> d(1);
  std::map<int, int> hist;
    for(int n=0; n<10000; ++n) {
        ++hist[2*d(gen)];
    }
    for(auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) 
                  << p.first/2.0 << '-' << (p.first+1)/2.0 <<
                ' ' << std::string(p.second/200, '*') << '\n';
    }
    
  std::cout << "Start Simulation with " << _npart << " particles!" << std::endl;
  
  for(int i=0; i<Npart; ++i) particles[i].init();
  for(int i=0; i<Npart; ++i) particles[i].setPos(1.1);
  for(int i=0; i<Npart; ++i) particles[i].setVel(2.2);
  for(int i=0; i<Npart; ++i) particles[i].setF(3.3);  
  for(int i=0; i<Npart; ++i) particles[i].setBound(4);  
  
  for(int i=0; i<Npart; ++i) std::cout << particles[i].getPos() << std::endl;
  for(int i=0; i<Npart; ++i) std::cout << particles[i].getVel() << std::endl;
  for(int i=0; i<Npart; ++i) std::cout << particles[i].getF() << std::endl;  
  for(int i=0; i<Npart; ++i) std::cout << particles[i].getBound() << std::endl;  
  
  delete particles;
}

void LJSimulation :: start() {std::cout << "START" << std::endl;}
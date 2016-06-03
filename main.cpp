#include "LJSimulation.hpp"

using namespace std;

int main(int argc, char** argv) 
{
  int N = 512;
  int nstep = 1000;
  
  LJSimulation sim;
  
  sim.init();
  sim.set_number_of_particles(N);  
  sim.set_number_of_steps(nstep);
  
  sim.start();

  return 0;
}
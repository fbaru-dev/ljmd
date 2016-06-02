#include "LJSimulation.hpp"

using namespace std;

int main(int argc, char** argv) 
{
  int N = 50;
  int nstep = 10;
  
  LJSimulation sim;
  
  sim.init();
  sim.set_number_of_particles(N);  
  sim.set_number_of_steps(nstep);
  
  sim.start();

  return 0;
}